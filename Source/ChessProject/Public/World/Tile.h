// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessPawn.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Component)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=ChessPiece, ReplicatedUsing=OnRep_ChessPawn)
	AChessPawn* ChessPawn = nullptr;

	/**
	 * Called when the ChessPawn for the server instance of this tile changes and is replicated down.
	 * This is only ever executed on client side version of the game
	 * Never runs on server
	 */
	UFUNCTION()
	void OnRep_ChessPawn();
public:
	/**
	 * Used to set the ChessPawn for this tile
	 * This only happens on the server
	 * If called from client, the Remote Procedure Call (RPC) Server_SetChessPawn
	 * is called which routes this function to be called on the Server
	 */
	UFUNCTION(BlueprintCallable)
	void SetChessPawn(AChessPawn* Pawn);

private:
	/**
	 * Makes a call to the server to execute SetChessPawn
	 * Server functions are implemented as Server_SetChessPawn_Implementation
	 * Private as this should never be called outside of class
	 */
	UFUNCTION(Server, Reliable)
	void Server_SetChessPawn(AChessPawn* Pawn);
	
};
