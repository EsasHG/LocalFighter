// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementComp.h"
#include "Dot.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UMovementComp::UMovementComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("MovementComp Created!"))
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
	UE_LOG(LogTemp, Warning, TEXT("Moving actor!"))
	
	// ...
}

void UMovementComp::MoveActor(float DeltaTime)
{
	if (DotToMove)
	{
		GetInputVector();
		UE_LOG(LogTemp, Warning, TEXT("Sucessfull cast to Dot! %f"), InputVector.X)
		FVector Velocity = CalculateVelocity();
		DotToMove->SetActorLocation(DotToMove->GetActorLocation() + (Velocity*Acceleration*DeltaTime), true);
		//CurrSpeed = Velocity.Size();
	}
}

void UMovementComp::GetInputVector()
{
	if (DotToMove)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got input vector! %f"), InputVector.X)
		InputVector = DotToMove->GetDirection().GetClampedToMaxSize(1);
		//InputVector = FVector(x, y, z).GetClampedToMaxSize(1);
	}
}

FVector UMovementComp::CalculateVelocity()
{

	return (InputVector);

}
