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

	ADot();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetInputUp(float Value);
	void GetInputRight(float Value);
	void ShootUp(float Value);
	void ShootRight(float Value);
	void ShootPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UMovementComp* MovementComponent = nullptr;

	UFUNCTION(BlueprintCallable)
	float GetScore() { return WinCounter; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartExpanding();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopExpanding();

	FVector2D GetDirection() { return Direction; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* Sprite = nullptr;
	bool bHasRun = false;

	UPROPERTY(EditAnywhere)
	float ShootRate{ 0.1 };
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* GunSprite = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UClass* Bullet = nullptr;

	FTimerHandle TH_GoalCounter;
	FTimerHandle TH_ShootCounter;
	FTimerHandle TH_ChargeShot;
	FTimerHandle TH_ResetCollision;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void Shoot(FVector Scale = FVector(1));

	void ChargeShot();
	void StopCharge();
	void StartCounting() { WinCounter += 0.1; }
	void SetShootingTrue() { bCanShoot = true; bTimerIsSet = false; }
	void CollisionCanRun() { bHasRun = false; }

	FVector2D Direction{ 0.f, 0.f };
	FVector2D ShootDirection{ 1.f, 0.f };
	FVector2D AimDirection{ 0.f, 0.f };

	float WinCounter{ 0 };

	bool bCanShoot = true;
	bool bTimerIsSet = false;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShootingSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ChargingSound;

	
	
};