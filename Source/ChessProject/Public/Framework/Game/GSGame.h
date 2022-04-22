// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GMGame.h"
#include "GameFramework/GameState.h"
#include "GSGame.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AGSGame : public AGameState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetPlayerTurn(const FPlayerInfo& PlayerInfo);
protected:
	UPROPERTY(ReplicatedUsing=OnRep_PlayerTurn)
	ETeams PlayerTurn = ETeams::None;

	/**
	 * Can use this function on turn change to detect if its the local players turn
	 */
	UFUNCTION()
	void OnRep_PlayerTurn();
};
