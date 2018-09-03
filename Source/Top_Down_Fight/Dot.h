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
	UPROPERTY(VisibleAnywhere)
	float WinCounter{ 0 };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	class UMovementComp* GetMovementComp() { return MovementComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UMovementComp* MovementComponent = nullptr;

	FVector2D GetDirection() { return Direction; }
	UFUNCTION(BlueprintCallable)
	float GetScore() { return WinCounter; }
private:

	UPROPERTY(VisibleAnywhere)
		class UPaperSpriteComponent* Sprite = nullptr;

	UPROPERTY(VisibleAnywhere)
		class UPaperSpriteComponent* GunSprite = nullptr;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Sphere = nullptr;

	FTimerHandle TH_GoalCounter;
	FTimerHandle TH_ShootCounter;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void GetInputUp(float Value);
	void GetInputRight(float Value);
	void ShootUp(float Value);
	void ShootRight(float Value);
	void Shoot();
	void StartCounting();
	void SetShootingTrue() { bCanShoot = true; }

	FVector2D Direction{ 0.f, 0.f };
	FVector2D ShootDirection{ 1.f, 0.f };
	FVector2D AimDirection{ 0.f, 0.f };

	UPROPERTY(EditDefaultsOnly)
	float Speed = 1000;

	UPROPERTY(EditDefaultsOnly)
	float ShootRate = 0.2;

	bool bCanShoot = true;

	UPROPERTY(EditDefaultsOnly)
	UClass* Bullet = nullptr;

	
	
};