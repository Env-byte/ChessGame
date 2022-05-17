// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "World/ChessPiece.h"
#include "PSGame.generated.h"

class APCGame;

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
	FPlayerInfo(): PlayerController(nullptr), Team()
	{
	}

	FPlayerInfo(APCGame* PlayerControllerIn, const ETeams TeamIn, const bool bIsFirstIn):
		PlayerController(PlayerControllerIn), Team(TeamIn), bIsFirst(bIsFirstIn)
	{
	}

	/**
	 * The player controller for this player, this will be null if replicated to a player that doesn't own the controller
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APCGame* PlayerController;

	/**
	 * Which team this player belongs too
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETeams Team;

	/**
	 * Whether this player is going first or second
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFirst = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AChessPiece*> ChessPieces;
};

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API APSGame : public APlayerState
{
	GENERATED_BODY()
protected:
	UPROPERTY(ReplicatedUsing=OnRep_SelectedPiece)
	AChessPiece* SelectedPiece;

	UFUNCTION()
	void OnRep_SelectedPiece();
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION(Server, Reliable)
	void Server_SetSelectedPiece(AChessPiece* ChessPiece);
	
public:
	UFUNCTION()
	void SetSelectedPiece( AChessPiece* ChessPiece);

	UPROPERTY(BlueprintReadOnly, Replicated)
	FPlayerInfo PlayerInfo;

	virtual void BeginPlay() override;
};
