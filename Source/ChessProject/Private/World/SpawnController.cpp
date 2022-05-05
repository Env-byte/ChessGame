// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SpawnController.h"

// Sets default values
ASpawnController::ASpawnController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawnController::BeginPlay()
{
	Super::BeginPlay();
}

TMap<ETeams, APlayerSpawn*> ASpawnController::GenerateSpawns(ATileController* TileController)
{
	TMap<ETeams, APlayerSpawn*> PlayerSpawns;
	for (const ATile* Tile : TileController->GetTiles())
	{
		if (Tile->TileInfo.Row == 0 || TileController->TileControllerSettings.Rows == Tile->TileInfo.Row)
		{
			APlayerSpawn* PlayerSpawn = APlayerSpawn::StartSpawnActor(this, SpawnerClass);
			PlayerSpawn->Team = Tile->TileInfo.Team;
			FTransform Transform;
			Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
			Transform.SetLocation(FVector(0.f, Tile->GetActorLocation().Y, GetActorLocation().Z));

			PlayerSpawn->FinishSpawn(Transform);

			PlayerSpawns.Add(Tile->TileInfo.Team, PlayerSpawn);
		}
		if (PlayerSpawns.Find(ETeams::Blue) != nullptr && PlayerSpawns.Find(ETeams::Red) != nullptr)
		{
			break;
		}
	}

	return PlayerSpawns;
}
