// Fill out your copyright notice in the Description page of Project Settings.

#include "Dot.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"

#include "Projectile.h"
#include "MovementComp.h"
#include "Island.h"
#include "Wall.h"


// Sets default values
ADot::ADot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere"); 
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
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ADot::OnOverlapEnd);
}

// Called every frame
void ADot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GunSprite)
	{
		//FVector(ShootDirection.X*ShootDirection.X, -1, ShootDirection.Y*ShootDirection.Y) * 300
		ShootDirection.Normalize();
		GunSprite->SetRelativeLocation(FVector(ShootDirection.X, 0, ShootDirection.Y)*100);
	}

	if (!AimDirection.IsZero())
	{
		ShootDirection = AimDirection.GetSafeNormal();
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



void ADot::Shoot()
{
	if (!ShootDirection.IsZero())
	{

		//something seems to be wrong here
		FActorSpawnParameters Params;
		Params.Instigator = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AProjectile* NewBullet = GetWorld()->SpawnActor<AProjectile>(Bullet, GetActorLocation() + FVector(ShootDirection.GetSafeNormal(), 0) * 150, GetActorRotation() + FRotator(0, 0, 90),Params);
		
		if (!NewBullet) {
			UE_LOG(LogTemp, Error, TEXT("Bullet not spawned!!"));
			return; 
		}
		NewBullet->SetDirection(ShootDirection);
	}
}



void ADot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Dot overlap begins!"));
	ADot* OtherDot = Cast<ADot>(OtherActor);
	if (Cast<AIsland>(OtherActor))
	{ 
		GetWorld()->GetTimerManager().SetTimer(TH_GoalCounter, this, &ADot::StartCounting, 0.1f, true);
	}
	else if (OtherDot)
	{
		MovementComponent->SendForce(OtherDot);
	}
	else if (Cast<AWall>(OtherActor))
	{
		MovementComponent->PrevVelocity = FVector2D{ 0,0 };
	}
}

void ADot::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Dot overlap Ends!"));
	if (Cast<AIsland>(OtherActor))
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_GoalCounter);
	}
}

void ADot::StartCounting()
{
	WinCounter += 0.1;
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
	AimDirection.X = Value;
}

void ADot::ShootRight(float Value)
{
	AimDirection.Y = Value;
}