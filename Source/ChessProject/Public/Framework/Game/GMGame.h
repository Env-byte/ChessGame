// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/GameMode.h"
#include "GMGame.generated.h"

enum class ETeams : uint8;
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
};

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AGMGame : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FPlayerInfo> ConnectedPlayers;

public:
	UFUNCTION(BlueprintCallable)
	FPlayerInfo GetConnectedPlayer(ETeams Team);

protected:
	////////// Players Joining //////////
	int32 ReadyPlayers = 0;
	/** if joining straight into the server */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Called when the player controller swaps after server travel */
	virtual void InitSeamlessTravelPlayer(AController* NewController) override;

	/**
	 * Handles a player joining the server from either server travel or direct login
	 */
	void HandlePlayerJoin(APCGame* PlayerController);

	/** Handle player leaving by removing from array of all players */
	virtual void Logout(AController* Exiting) override;

	/**
	 * When player joins spawn a camera and posses it 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnPlayerCamera(const FPlayerInfo& PlayerInfo);
public:
	/** When clientside is finished setting up, this function is called from the playerController */
	void PlayerControllerReady();
	////////// Players Joining //////////
protected:
	////////// Game Rules //////////
	////////// Game Rules //////////
};
