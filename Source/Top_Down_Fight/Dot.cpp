// Fill out your copyright notice in the Description page of Project Settings.

#include "Dot.h"
#include "Components/InputComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
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

	MovementComponent = CreateDefaultSubobject<UMovementComp>("MovementComp");
}

// Called when the game starts or when spawned
void ADot::BeginPlay()
{
	Super::BeginPlay();
	Sprite->AddWorldRotation(FQuat(FRotator(0, 0, 90)));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ADot::OnOverlapBegin);
}

// Called every frame
void ADot::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (MovementComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("cry Begins"));
	}

}

// Called to bind functionality to input
void ADot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADot::GetInputRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADot::GetInputUp);


}

void ADot::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begins"));
}

void ADot::GetInputUp(float Value)
{

	Direction.X = Value;
}

void ADot::GetInputRight(float Value)
{

	Direction.Y = Value;

}