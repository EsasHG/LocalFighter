// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"
#include "Public/TimerManager.h"
#include "DotController.h"
#include "Dot.h"


// Sets default values
AIsland::AIsland()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	Sprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AIsland::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AIsland::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AIsland::OnOverlapEnd);

}

// Called every frame
void AIsland::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIsland::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADot* player = Cast<ADot>(OtherActor);
	int id = -1; // a value no player will have
	if (player)
		id = UGameplayStatics::GetPlayerControllerID((Cast<APlayerController>(player->GetController())));

	//player 1
	if (id == 0)
	{
		p1Overlaps = 1;

		GetWorld()->GetTimerManager().SetTimer(TH_CountP1,this, &AIsland::AddP1Score, 0.1f, true);
		UE_LOG(LogTemp, Warning, TEXT("P1 found! Value: %f"), p1Score)
	}
	//player 2
	else if (player)
	{
		p2Overlaps = 1;

		GetWorld()->GetTimerManager().SetTimer(TH_CountP2, this, &AIsland::AddP2Score, 0.1f, true);
		UE_LOG(LogTemp, Warning, TEXT("P2 found! Value: %f"), p1Score)
	}

	OverlappingActors = p1Overlaps + p2Overlaps;
	UE_LOG(LogTemp, Warning, TEXT("Overlapping actors: %i"), OverlappingActors)


	if (OverlappingActors !=1)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountP1);
		GetWorld()->GetTimerManager().ClearTimer(TH_CountP2);
	}




	//int id = Cast<ADot>(OtherActor);
}

void AIsland::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	ADot* player = Cast<ADot>(OtherActor);
	int id = -1; // a value no player will have
	if (player)
		id = UGameplayStatics::GetPlayerControllerID((Cast<APlayerController>(Cast<ADot>(OtherActor)->GetController())));

	if (id == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountP1);
		p1Overlaps = 0;
		if (p2Overlaps == 1)
		{
			GetWorld()->GetTimerManager().SetTimer(TH_CountP2, this, &AIsland::AddP2Score, 0.1f, true);
		}

	}
	else if (player)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_CountP2);
		p2Overlaps = 0;
		if(p1Overlaps==1)
		GetWorld()->GetTimerManager().SetTimer(TH_CountP1, this, &AIsland::AddP1Score, 0.1f, true);

	}
	else {}

	OverlappingActors = p1Overlaps + p2Overlaps;

	UE_LOG(LogTemp, Warning, TEXT("Overlap ends"))
	UE_LOG(LogTemp, Warning, TEXT("Overlapping actors: %i"), OverlappingActors)




}



