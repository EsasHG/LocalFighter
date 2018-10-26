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

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		float GetP1Score() { return p1Score; }
	UFUNCTION(BlueprintCallable)
		float GetP2Score() { return p2Score; }
	//int getOverlappingActors() { return overlapingActors; }
private:	

	int OverlappingActors = 0;

	float p1Score=0;
	float p2Score=0;

	int p1Overlaps = 0;
	int p2Overlaps = 0;

	void AddP1Score() { p1Score += 0.1; };
	void AddP2Score() { p2Score += 0.1; };

	FTimerHandle TH_CountP1;
	FTimerHandle TH_CountP2;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* Sprite = nullptr;
	
};
