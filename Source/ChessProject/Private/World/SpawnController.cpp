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

TMap<ETeams, APlayerSpawn*> ASpawnController::GenerateSpawns(ATileController* TileController) const
{
	if (!HasAuthority())
	{
		return TMap<ETeams, APlayerSpawn*>{};
	}

	TMap<ETeams, APlayerSpawn*> PlayerSpawns;
	for (const ATile* Tile : TileController->GetTiles())
	{
		if ((Tile->TileInfo.Row == 0 || TileController->TileControllerSettings.Rows - 1 == Tile->TileInfo.Row) &&
			PlayerSpawns.Find(Tile->TileInfo.Team) == nullptr)
		{
			APlayerSpawn* PlayerSpawn = APlayerSpawn::StartSpawnActor(this, SpawnerClass);
			PlayerSpawn->Team = Tile->TileInfo.Team;
			FTransform Transform;;


			const float X = (TileController->TileControllerSettings.Cols - 1)
			* TileController->TileControllerSettings.Width / 2;
			float Y;
			FQuat Quat;

			if (Tile->TileInfo.Row == 0)
			{
				Quat = FQuat::MakeFromRotator(FRotator{-45.f, 90.f, 0.f});
				Y = Tile->GetActorLocation().Y - TileController->TileControllerSettings.Width * 2;
			}
			else
			{
				Quat = FQuat::MakeFromRotator(FRotator{-45.f, 270.f, 0.f});
				Y = Tile->GetActorLocation().Y + TileController->TileControllerSettings.Width * 2;
			}
			Transform.SetRotation(Quat);
			Transform.SetLocation(FVector(X,Y,GetActorLocation().Z));
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
