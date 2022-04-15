// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileController.generated.h"

class ATile;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Tiles")
	TArray<ATile*> Tiles;

	UFUNCTION(BlueprintCallable)
	void GenerateTiles();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Board)
	int32 Cols;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Board)
	int32 Rows;
};
