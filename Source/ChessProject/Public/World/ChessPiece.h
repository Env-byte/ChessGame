// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

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
class CHESSPROJECT_API AChessPiece : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChessPiece();

	/**
	 * The team this object belongs to
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Piece Info", ReplicatedUsing=OnRep_Team)
	ETeams Team = ETeams::Neutral;

	/**
	* The team this object belongs to
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Piece Info", ReplicatedUsing=OnRep_PieceType)
	EPieceTypes PieceType = EPieceTypes::None;

	/**
	 * This is needed to replicate the property ChessPawn
	 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	static AChessPiece* StartSpawnActor(const AActor* Owner, TSubclassOf<AChessPiece> ChessPawnClass);

	void FinishSpawn(const FTransform& Transform);


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
};
