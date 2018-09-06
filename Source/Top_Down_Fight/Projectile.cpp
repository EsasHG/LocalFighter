// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "PaperSpriteComponent.h"
#include "Dot.h"
#include "MovementComp.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	RootComponent = Sprite;

	InitialLifeSpan = 1.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sprite->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() +FVector(BulletDirection,0) * DeltaTime*BulletSpeed);
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ADot* Dot = Cast<ADot>(OtherActor);
	if (Dot && OtherActor != Instigator )
	{
		Dot->MovementComponent->AddForce(BulletDirection*BulletSpeed);
		Destroy();

	}
}

