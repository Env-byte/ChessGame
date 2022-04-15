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

UCLASS(Abstract)
class CHESSPROJECT_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team")
	ETeams Team = ETeams::Neutral;

	static ATile* StartSpawnActor(const AActor* Owner, TSubclassOf<ATile> TileClass);

	void FinishSpawn(const FTransform& Transform);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Controller)
	ATileController* TileController;

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
