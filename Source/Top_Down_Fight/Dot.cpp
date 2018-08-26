// Fill out your copyright notice in the Description page of Project Settings.

#include "Dot.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"

#include "Projectile.h"
#include "MovementComp.h"


// Sets default values
ADot::ADot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere"); 
	Sphere->bGenerateOverlapEvents = true;
	RootComponent = Sphere;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(Sphere);

	GunSprite = CreateDefaultSubobject<UPaperSpriteComponent>("GunSprite");
	GunSprite->SetupAttachment(Sprite);

	MovementComponent = CreateDefaultSubobject<UMovementComp>("MovementComp");
}

// Called when the game starts or when spawned
void ADot::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADot::OnOverlapBegin);
}

// Called every frame
void ADot::Tick(float DeltaTime)
{
	if (GunSprite)
	{
		//FVector(ShootDirection.X*ShootDirection.X, -1, ShootDirection.Y*ShootDirection.Y) * 300
		ShootDirection.Normalize();
		GunSprite->SetRelativeLocation(FVector(ShootDirection.X,-1, ShootDirection.Y)*300);
	}
	Super::Tick(DeltaTime);
	if (MovementComponent)
	{

	}

}

// Called to bind functionality to input
void ADot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADot::GetInputRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADot::GetInputUp);
	PlayerInputComponent->BindAxis("ShootUp", this, &ADot::ShootUp);
	PlayerInputComponent->BindAxis("ShootRight", this, &ADot::ShootRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ADot::Shoot);


}

void ADot::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begins"));
}

void ADot::Shoot()
{

	AProjectile* NewBullet = GetWorld()->SpawnActor<AProjectile>(Bullet, GetActorLocation() + FVector(ShootDirection.GetSafeNormal(),0) * 100 , GetActorRotation() + FRotator(0, 0, 90));
	ShootDirection.Normalize();
	NewBullet->SetDirection(ShootDirection);




}


void ADot::GetInputUp(float Value)
{
	Direction.X = Value;
}

void ADot::GetInputRight(float Value)
{

	Direction.Y = Value;

}

void ADot::ShootUp(float Value)
{
	ShootDirection.X = Value;
}

void ADot::ShootRight(float Value)
{
	ShootDirection.Y = Value;
}