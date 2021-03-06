// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DotController.generated.h"

/**
 * 
 */
UCLASS()
class TOP_DOWN_FIGHT_API ADotController : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	class ADot* AIPawn = nullptr;
	class AActor* Player = nullptr;
	
};
