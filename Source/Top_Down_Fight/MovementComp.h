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
	float MaxSpeed = 3000;
	float TurningBoost;
	FVector2D GetInputVector();

private:
	
	float AccelerationConst{ 50 };
	float DecelerationConst{ 50 };

	FVector2D PrevVelocity{ 0,0 };
	
	void MoveActor(float DeltaTime);

	FVector2D CalculateVelocity();

	class ADot * DotToMove = nullptr;
};