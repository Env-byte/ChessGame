// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "ChessProject/ChessProject.h"
#include "Components/SelectedPieceComponent.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

class UPieceMovementComponent;
UENUM(BlueprintType)
enum class EPieceTypes : uint8
{
	None,
	Knight,
	Pawn,
	Queen,
	King,
	Rook,
	Bishop
};

UCLASS(Abstract)
class CHESSPROJECT_API AChessPiece final : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChessPiece();

	/**
	 * The team this object belongs to
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Piece Info", ReplicatedUsing=OnRep_Team)
	ETeams Team = ETeams::None;

	/**
	* The team this object belongs to
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Piece Info", ReplicatedUsing=OnRep_PieceType)
	EPieceTypes PieceType = EPieceTypes::None;

	/**
	 * This controls the movement of the chess piece
	 * also used to display the movement by changing the tile colours
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UPieceMovementComponent* PieceMovementComponent;

	/**
	* This Component is used to display which chess piece is currently selected
	* 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	USelectedPieceComponent* SelectedPieceComponent;

	/**
	 * This is needed to replicate the property ChessPawn
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Used to start spawning this chess piece
	 */
	static AChessPiece* StartSpawnActor(const AActor* Owner, TSubclassOf<AChessPiece> ChessPawnClass);

	/**
	 * This is used to finalise the spawn after setting default values
	 */
	void FinishSpawn(const FTransform& Transform);

	UPROPERTY(ReplicatedUsing=OnRep_Tile)
	ATile* Tile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Component)
	UStaticMeshComponent* ChessPieceMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Component)
	USceneComponent* PivotOffsetComponent;

	UFUNCTION()
	void OnRep_Team();
	UFUNCTION()
	void OnRep_PieceType();
	UFUNCTION()
	void OnRep_Tile();
};
