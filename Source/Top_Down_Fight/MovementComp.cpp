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
		//CurrSpeed = Velocity.Size();
	}
}

void UMovementComp::GetInputVector()
{
	if (DotToMove)
	{
		InputVector = DotToMove->GetDirection().ClampAxes(-1,1);
	}
}

FVector2D UMovementComp::CalculateVelocity()
{
	GetInputVector();

	FVector2D Velocity;

	//if turn
	if ((FVector2D(0,0).CrossProduct(LastInputVector, InputVector) == 0) && (InputVector != LastInputVector) && InputVector != FVector2D(0, 0) && (LastInputVector != FVector2D(0, 0)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Turning 180! %f"), abs(InputVector.Size()));
		CurrSpeed = -abs(CurrSpeed -Deceleration);
		Velocity = InputVector * CurrSpeed;
		LastInputVector = InputVector;
	}
	else if ((InputVector != LastInputVector) && InputVector != FVector2D(0, 0) && (LastInputVector != FVector2D(0, 0)))
	{
			UE_LOG(LogTemp, Warning, TEXT("Turning! %f"), abs(InputVector.Size()));
			CurrSpeed = CurrSpeed/2;
			Velocity = InputVector * CurrSpeed;
			LastInputVector = InputVector;
		
	}
	else if ((CurrSpeed <= MaxSpeed) && (InputVector != FVector2D(0, 0)))
	{
		//continiue on path
		CurrSpeed += Acceleration;

		Velocity = InputVector * CurrSpeed;
		LastInputVector = InputVector;
	}
	else
	{
		if (CurrSpeed > 0)
		{
			CurrSpeed -= Deceleration;
		}
		Velocity = LastInputVector * CurrSpeed;
	}
	return Velocity;
}
