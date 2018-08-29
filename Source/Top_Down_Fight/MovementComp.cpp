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
	//GetInputVector();

	/*FVector2D InputVectorTested;
	if (InputVector.IsZero())
	{
		InputVectorTested = LastInputVector;
	}
	else
	{
		InputVectorTested = InputVector;
	}


	//if 180
	if ((LastInputVector.CrossProduct(LastInputVector, InputVector) == 0) && (InputVector != LastInputVector) && !InputVector.IsZero() && !LastInputVector.IsZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Turning 180! %f"), abs(InputVector.Size()));
		//CurrSpeed = -abs(CurrSpeed -Deceleration);
		Velocity = InputVectorTested * CurrSpeed;
		LastInputVector = InputVectorTested;
	}
	else if ((InputVector != LastInputVector) && !InputVector.IsZero() && !LastInputVector.IsZero())
	{
		//if turn
			UE_LOG(LogTemp, Warning, TEXT("Turning! %f"), abs(InputVector.Size()));
			FVector2D C = FMath::Lerp(LastInputVector, InputVectorTested, 0.5);
			Velocity = C * CurrSpeed;
			LastInputVector = C;
		
	}
	else if ((CurrSpeed <= MaxSpeed) && (!InputVector.IsZero()))
	{
		//continiue on path
		CurrSpeed += Acceleration;

		Velocity = InputVectorTested * CurrSpeed;
		LastInputVector = InputVectorTested;
	}
	else
	{
		if (CurrSpeed > 0)
		{
			CurrSpeed -= Acceleration;
		}
		if (CurrSpeed < 0)
			CurrSpeed = 0;
		Velocity = LastInputVector * CurrSpeed;
	}
	*/
	//calculate speed

	


	////makes sure it knows which way to go when you stop moving
	//if (InputVector.IsZero())
	//{
	//	Direction = LastInputVector;
	//	CurrSpeed -= Deceleration;
	//}
	//else if ((InputVector != LastInputVector) && !InputVector.IsZero() && !LastInputVector.IsZero() && (FMath::RadiansToDegrees(FMath::Acos(FVector2D::DotProduct(InputVector, LastInputVector) / InputVector.Size()*LastInputVector.Size())) > 1))//FVector2D::Distance(InputVector, LastInputVector) > 0.05))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Turning! %f"),FMath::RadiansToDegrees( FMath::Acos(FVector2D::DotProduct(InputVector, LastInputVector) / InputVector.Size()*LastInputVector.Size())));
	//
	//	
	//	CurrSpeed -= (FVector2D::DotProduct(InputVector, LastInputVector) / InputVector.Size()*LastInputVector.Size());
	//	Direction = LastInputVector;
	//	LastInputVector = FMath::Lerp(InputVector, LastInputVector,0.7);

	//	
	//	
	//}
	//else
	//{

	//	CurrSpeed +=Acceleration;


	//	Direction = InputVector;
	//	LastInputVector = InputVector;
	//}

	////makes sure CurrSpeed is valid
	//if (CurrSpeed > MaxSpeed)
	//	CurrSpeed = MaxSpeed;
	//if (CurrSpeed < 0)
	//	CurrSpeed = 0;
	//

	//FVector2D Velocity = Direction * CurrSpeed;
	
	FVector2D InputVector = GetInputVector();
	Acceleration = GetInputVector()* AccelerationConst;
	FVector2D Velocity = PrevVelocity + Acceleration;
	PrevVelocity = Velocity;

	if (Velocity.Size() > MaxSpeed)
	{
		Velocity = Velocity.GetSafeNormal()*MaxSpeed;
	}


	return Velocity;
}
