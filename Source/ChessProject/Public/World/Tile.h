// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class AChessPiece;
class ATileController;

UENUM(BlueprintType)
enum class ETileColour :uint8
{
	Black,
	White
};

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	int32 Col;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	int32 Row;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Position)
	ETileColour TileColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Team")
	ETeams Team = ETeams::None;
};

UCLASS(Abstract)
class CHESSPROJECT_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	/**
	 * This is needed to replicate the property ChessPawn
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	static ATile* StartSpawnActor(const AActor* Owner, TSubclassOf<ATile> TileClass);

	void FinishSpawn(const FTransform& Transform);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Controller, Replicated)
	ATileController* TileController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FTileInfo TileInfo;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Component)
	UStaticMeshComponent* TileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=ChessPiece, ReplicatedUsing=OnRep_ChessPiece)
	AChessPiece* ChessPiece = nullptr;

	/**
	 * Called when the ChessPawn for the server instance of this tile changes and is replicated down.
	 * This is only ever executed on client side version of the game
	 * Never runs on server
	 */
	UFUNCTION()
	void OnRep_ChessPiece();
public:
	/**
	 * Used to set the ChessPawn for this tile
	 * This only happens on the server
	 * If called from client, the Remote Procedure Call (RPC) Server_SetChessPawn
	 * is called which routes this function to be called on the Server
	 */
	UFUNCTION(BlueprintCallable)
	void SetChessPiece(AChessPiece* Pawn);

	FORCEINLINE AChessPiece* GetChessPiece() const { return ChessPiece; }

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_AddHighlight();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_RemoveHighlight();
private:
	/**
	 * Makes a call to the server to execute SetChessPawn
	 * Server functions are implemented as Server_SetChessPawn_Implementation
	 * Private as this should never be called outside of class
	 */
	UFUNCTION(Server, Reliable)
	void Server_SetChessPiece(AChessPiece* Pawn);
};
