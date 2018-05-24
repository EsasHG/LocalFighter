// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Dot.generated.h"

UCLASS()
class TOP_DOWN_FIGHT_API ADot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* Sprite = nullptr;

	UPROPERTY(VisibleAnywhere)
		class UFloatingPawnMovement* MovementComponent = nullptr;
	

	void MoveUp(float AxisValue);

	void MoveRight(float AxisValue);

	
	
};
