// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerSpawn.h"
#include "TileController.h"
#include "GameFramework/Actor.h"
#include "SpawnController.generated.h"

UCLASS()
class CHESSPROJECT_API ASpawnController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawner)
	TSubclassOf<APlayerSpawn> SpawnerClass;
public:
	/**
	 * Generate Spawns using the size of the board to help guide where to place them
	 */
	TMap<ETeams, APlayerSpawn*> GenerateSpawns(ATileController* TileController) const;
	static ASpawnController* Get(const UWorld* World);
};
