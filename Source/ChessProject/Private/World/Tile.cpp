// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Tile.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

ATile* ATile::StartSpawnActor(const AActor* Owner, const TSubclassOf<ATile> TileClass)
{
	const UWorld* World = Owner->GetWorld();
	const FTransform Transform = {};

	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(
		World,
		TileClass,
		Transform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (Actor == nullptr)
	{
		return nullptr;
	}

	ATile* Tile = Cast<ATile>(Actor);
	return Tile;
}

void ATile::FinishSpawn(const FTransform& Transform)
{
	UGameplayStatics::FinishSpawningActor(this, Transform);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}