// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TwoPlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOP_DOWN_FIGHT_API ATwoPlayerGameMode : public AGameMode
{
	GENERATED_BODY()
		ATwoPlayerGameMode();

		virtual void BeginPlay() override;
	
	
	
	
};
