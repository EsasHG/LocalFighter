// Fill out your copyright notice in the Description page of Project Settings.

#include "Dot.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ADot::ADot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	RootComponent = Sprite;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");

	MovementComponent->Acceleration = 400;
	MovementComponent->TurningBoost = 1000;
}

// Called when the game starts or when spawned
void ADot::BeginPlay()
{
	Super::BeginPlay();
	Sprite->AddWorldRotation(FQuat(FRotator(0, 0, 90)));
}

// Called every frame
void ADot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovementComponent->AddInputVector((Direction.GetClampedToMaxSize(1) * Speed * DeltaTime));
}

// Called to bind functionality to input
void ADot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADot::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADot::MoveUp);
}

void ADot::MoveUp(float Value)
{
	Direction.X = Value;
}

void ADot::MoveRight(float Value)
{

	Direction.Y = Value;

}