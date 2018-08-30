// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Island.generated.h"

UCLASS()
class TOP_DOWN_FIGHT_API AIsland : public AActor
{
	GENERATED_BODY()
	
public:	

	AIsland();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* Sprite = nullptr;
	
};
