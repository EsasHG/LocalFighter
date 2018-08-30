// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOP_DOWN_FIGHT_API AProjectile : public AActor
{
	GENERATED_BODY()


public:	
	AProjectile();
	void SetDirection(FVector2D Value) { BulletDirection = Value.GetSafeNormal(); }

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* Sprite = nullptr;

private: 
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	FVector2D BulletDirection = FVector2D(0,0);
	float BulletSpeed = 3000;
};
