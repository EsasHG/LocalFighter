// Fill out your copyright notice in the Description page of Project Settings.

#include "DotController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Dot.h"
void ADotController::BeginPlay()
{
	Super::BeginPlay();
	AIPawn = Cast<ADot>(GetPawn());
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UE_LOG(LogTemp, Warning, TEXT("AI RUNS"))
}

void ADotController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(AIPawn)
	{ 
		FVector DirVec = FVector(0.f) - AIPawn->GetActorLocation();
		FVector ShootDir = (Player->GetActorLocation() + FMath::RandRange(-200,200))- AIPawn->GetActorLocation();
		
		
		AIPawn->GetInputUp(DirVec.X);
		AIPawn->GetInputRight(DirVec.Y);
		AIPawn->ShootUp(ShootDir.X);
		AIPawn->ShootRight(ShootDir.Y);
		AIPawn->ShootPressed();


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn"))
	}
}

