// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovementComp.generated.h"


class ADot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class TOP_DOWN_FIGHT_API UMovementComp : public UActorComponent
{
	GENERATED_BODY()

public:	

	UMovementComp();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddForce(FVector2D fIn);
	void SendForce(ADot* DotIn);
	FVector2D GetVelocity() { return PrevVelocity; }
	FVector2D PrevVelocity{ 0,0 };
	UPROPERTY(EditAnywhere)
	float MaxSpeed = 2500;
private:

	UPROPERTY(EditAnywhere)
	float AccelerationConst{ 60 };

	UPROPERTY(EditAnywhere)
	float DecelerationConst{ 50 };
	float TurningBoost;


	
	void MoveActor(float DeltaTime);
	FVector2D GetInputVector();
	FVector2D CalculateVelocity();


	class ADot * DotToMove = nullptr;
};