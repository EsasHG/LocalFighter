// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PaperSpriteComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Bullet Spawned! Direction: %f, %f"), BulletDirection.X, BulletDirection.Y);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() +FVector(BulletDirection,0) * DeltaTime*BulletSpeed);
}

