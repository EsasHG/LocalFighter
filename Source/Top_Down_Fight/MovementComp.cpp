// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementComp.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Dot.h"


// Sets default values for this component's properties
UMovementComp::UMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
		
	UE_LOG(LogTemp, Warning, TEXT("MovementComp Created!"));
	// ...
}


// Called when the game starts
void UMovementComp::BeginPlay()
{
	Super::BeginPlay();

	DotToMove = Cast<ADot>(GetOwner());

	// ...

}


// Called every frame
void UMovementComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MoveActor(DeltaTime);

	
	// ...
}

void UMovementComp::MoveActor(float DeltaTime)
{
	if (DotToMove)
	{
		DotToMove->SetActorLocation(DotToMove->GetActorLocation() + FVector(CalculateVelocity() *DeltaTime, 0), true);
		


	}
}

FVector2D UMovementComp::GetInputVector()
{
	if (DotToMove)
	{
		return DotToMove->GetDirection().GetSafeNormal();
	}
	return FVector2D(0, 0);
}

FVector2D UMovementComp::CalculateVelocity()
{
	FVector2D InputVector = GetInputVector();
	FVector2D Acceleration = GetInputVector()* AccelerationConst;
	FVector2D Velocity = PrevVelocity + Acceleration - PrevVelocity/DecelerationConst;
	PrevVelocity = Velocity;

	//TODO bytt til fvector, bruk ClampToMaxSize for å slippe if-testen
	if (Velocity.Size() > MaxSpeed)
	{
		Velocity = Velocity.GetSafeNormal()*MaxSpeed;
	}

	return Velocity;
}

//gets called on overlap with bullet
void UMovementComp::AddForce(FVector2D fIn)
{
	PrevVelocity = fIn;
	UE_LOG(LogTemp, Warning, TEXT("Adding force!!"));
}
