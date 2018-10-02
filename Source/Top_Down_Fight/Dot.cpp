// Fill out your copyright notice in the Description page of Project Settings.

#include "Dot.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Math/UnrealMathUtility.h"

#include "Projectile.h"
#include "MovementComp.h"
#include "Island.h"
#include "Wall.h"


// Sets default values
ADot::ADot()
{
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
	
	ShootDirection.Normalize();
	if (GunSprite)
	{
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
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ADot::ShootPressed);
	PlayerInputComponent->BindAction("Shoot", IE_Repeat, this, &ADot::ShootPressed);
	PlayerInputComponent->BindAction("ChargedShot", IE_Pressed, this, &ADot::ChargeShot);
	PlayerInputComponent->BindAction("ChargedShot", IE_Released, this, &ADot::StopCharge);

}

void ADot::Shoot(FVector Scale)
{
	if (bCanShoot && !ShootDirection.IsZero())
	{
		//something seems to be wrong here
		FActorSpawnParameters Params;
		Params.Instigator = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AProjectile* NewBullet = GetWorld()->SpawnActor<AProjectile>(Bullet, GetActorLocation() + FVector(ShootDirection.GetSafeNormal(), 0) * 150, GetActorRotation() + FRotator(0, 0, 90), Params);
		
		if (NewBullet) 
		{

			NewBullet->SetDirection(ShootDirection);
			NewBullet->SetActorRelativeScale3D(Scale);
			bCanShoot = false;
			GetWorld()->GetTimerManager().SetTimer(TH_ShootCounter, this, &ADot::SetShootingTrue, ShootRate, true);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootingSound, GetActorLocation(),1, FMath::FRandRange(0.8,1.2));
		}
	}
}

void ADot::ShootPressed()
{
	Shoot(FVector(0.1));
}

void ADot::ChargeShot()
{
	if (MovementComponent)
		MovementComponent->bMoveIsAllowed = false;
	UE_LOG(LogTemp, Warning, TEXT("Charing Shot!"))
	StartExpanding();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ChargingSound, GetActorLocation(), 1, FMath::FRandRange(0.8, 1.2));
	GetWorld()->GetTimerManager().SetTimer(TH_ChargeShot, this, &ADot::StopCharge, 1, false);
}

void ADot::StopCharge()
{
	if (MovementComponent && MovementComponent->bMoveIsAllowed == false)
	{
		StopExpanding();
		MovementComponent->bMoveIsAllowed = true;
		Shoot(FVector(GetWorld()->GetTimerManager().GetTimerElapsed(TH_ChargeShot) / 2));
		GetWorld()->GetTimerManager().ClearTimer(TH_ChargeShot);
	}
}

void ADot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADot* OtherDot = Cast<ADot>(OtherActor);
	if (Cast<AIsland>(OtherActor))
	{
		GetWorld()->GetTimerManager().SetTimer(TH_GoalCounter, this, &ADot::StartCounting, 0.1f, true);
		//MovementComponent->MaxSpeed = 1500;


	}
	else if (OtherDot)
	{
		MovementComponent->SendForce(OtherDot);
	}
	else 
	{
		AWall* Wall = Cast<AWall>(OtherActor);
		if (Wall)
		{
			if (Wall->GetIsHorizontalWall())
			{
				MovementComponent->PrevVelocity = FVector2D{ -MovementComponent->PrevVelocity.X, MovementComponent->PrevVelocity.Y };
			}
			else
			{
				MovementComponent->PrevVelocity = FVector2D{ MovementComponent->PrevVelocity.X, -MovementComponent->PrevVelocity.Y };
			}
		}
	}
}

void ADot::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AIsland>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Dot overlap Ends!"));
		GetWorld()->GetTimerManager().ClearTimer(TH_GoalCounter);
		MovementComponent->MaxSpeed = 2500;
	}
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