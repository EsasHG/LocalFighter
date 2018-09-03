// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class TOP_DOWN_FIGHT_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh = nullptr;

	bool GetIsHorizontalWall() { return bIsHorizontalWall; }
private:

	UPROPERTY(EditAnywhere)
	bool bIsHorizontalWall = false;
	
	
};
