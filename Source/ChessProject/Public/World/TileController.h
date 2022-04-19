// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "Framework/Game/PCGame.h"
#include "GameFramework/Actor.h"
#include "TileController.generated.h"

UENUM(BlueprintType)
enum ETileControllerState
{
	NotStarted,
	Started,
	Finished
};

USTRUCT(BlueprintType)
struct FTileControllerSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	int32 Cols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TileWidth)
	float Width = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	TSubclassOf<ATile> TileClass;
};

UCLASS()
class CHESSPROJECT_API ATileController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileController();

	FORCEINLINE ETileControllerState GetControllerState() const { return ControllerState; };

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	ETileControllerState ControllerState = NotStarted;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Tiles", Replicated)
	TArray<ATile*> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ControllerSettings)
	FTileControllerSettings TileControllerSettings;

	/////////////// Defer Spawn ///////////////
	/**
	 * Generate Tiles
	 * This only happens on Server
	 * Tiles are set to hidden initially 
	 */
	void GenerateTiles();
	AChessPiece* GetChessPiece(const APCGame* PlayerController, int32 Col, int32 Row);

	/**
	 * Generate Tile
	 */
	void GenerateTile(int32 Col, int32 Row);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnTime)
	float TimerScale = 0.005f;

	FTimerHandle Handle;

	/** 
	 * Called From Server to show tiles on all connected clients
	 */
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_ShowTiles();

	void ShowTile(ATile* Tile);
	/////////////// Defer Spawn ///////////////
};
