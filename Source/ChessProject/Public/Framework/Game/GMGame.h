// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSGame.h"
#include "ChessProject/ChessProject.h"
#include "GameFramework/GameMode.h"
#include "GMGame.generated.h"

class APSGame;
class APlayerSpawn;
class APCGame;

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AGMGame : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<APSGame*> ConnectedPlayers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<ETeams, APlayerSpawn*> PlayerSpawns;
public:
	UFUNCTION(BlueprintCallable)
	void GetConnectedPlayer(ETeams Team, FPlayerInfo& PlayerInfoOut);

	virtual void BeginPlay() override;
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
	void BP_SpawnPlayerCamera(const FPlayerInfo& PlayerInfo);
public:
	/** When clientside is finished setting up, this function is called from the playerController */
	void PlayerControllerReady();
	////////// Players Joining //////////
protected:
	////////// Game Rules //////////
	////////// Game Rules //////////
};
