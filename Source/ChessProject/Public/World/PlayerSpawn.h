// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/Actor.h"
#include "PlayerSpawn.generated.h"

UCLASS()
class CHESSPROJECT_API APlayerSpawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerSpawn();

	/**
	 * The team which should spawn at this actor
	 */
	UPROPERTY(BlueprintReadOnly, Category=Team,meta=(ExposeOnSpawn))
	ETeams Team;

	static APlayerSpawn* StartSpawnActor(const AActor* Owner, TSubclassOf<APlayerSpawn> SpawnClass);

	void FinishSpawn(const FTransform& Transform);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
