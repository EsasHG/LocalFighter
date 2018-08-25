// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class TOP_DOWN_FIGHT_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	float Acceleration = 100;
	float Deceleration;
	float TurningBoost;
	void GetInputVector();


private:
	
	float CurrSpeed{ 0 };

	FVector InputVector;
	
	void MoveActor(float DeltaTime);

	FVector CalculateVelocity();

	class ADot * DotToMove = nullptr;
};
