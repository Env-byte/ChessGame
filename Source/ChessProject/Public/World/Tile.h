// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class ATileController;

UENUM(BlueprintType)
enum class ETileColour :uint8
{
	Black,
	White
};

UCLASS()
class CHESSPROJECT_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team")
	ETeams Team = ETeams::Neutral;

	static ATile* StartSpawnActor();

	void FinishSpawn(const FTransform& Transform);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=TileWidth)
	float Width = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	int32 Col;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	int32 Row;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	ETileColour TileColour;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Static)
	UStaticMeshComponent* StaticMesh;
};
