// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PlayerSpawn.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerSpawn::APlayerSpawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

APlayerSpawn* APlayerSpawn::StartSpawnActor(const AActor* Owner, const TSubclassOf<APlayerSpawn> SpawnClass)
{
	const UWorld* World = Owner->GetWorld();
	const FTransform Transform = {};

	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(
		World,
		SpawnClass,
		Transform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (Actor == nullptr)
	{
		return nullptr;
	}

	APlayerSpawn* Spawn = Cast<APlayerSpawn>(Actor);
	return Spawn;
}

void APlayerSpawn::FinishSpawn(const FTransform& Transform)
{
	UGameplayStatics::FinishSpawningActor(this, Transform);

}

// Called when the game starts or when spawned
void APlayerSpawn::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/PlayerSpawn"))));
#endif
}
