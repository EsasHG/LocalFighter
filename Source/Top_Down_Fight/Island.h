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
	//int getOverlappingActors() { return overlapingActors; }
private:	

	int overlapingActors = 0;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* Sprite = nullptr;
	
};
