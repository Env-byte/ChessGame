// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "TileController.generated.h"

UCLASS()
class CHESSPROJECT_API ATileController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( BlueprintReadWrite, Category="Tiles")
	TArray<ATile*> Tiles;

	UFUNCTION(BlueprintCallable)
	void GenerateTiles();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	int32 Cols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TileWidth)
	float Width = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Board)
	TSubclassOf<ATile> TileClass;


	/////////////// Defer Spawn ///////////////
	FTimerHandle ColHandle;
	FTimerHandle RowHandle;
	int32 CurrentCol;
	int32 CurrentRow;

	void HandleCol();
	void HandleRow();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SpawnTime)
	float Timer = 1.5f;
	
	UFUNCTION(BlueprintCallable)
	void GenerateTilesDefer();
	/////////////// Defer Spawn ///////////////
};
