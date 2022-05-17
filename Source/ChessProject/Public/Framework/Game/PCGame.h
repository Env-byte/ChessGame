// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GSGame.h"
#include "PSGame.h"
#include "GameFramework/PlayerController.h"
#include "PCGame.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurnChange, bool, bThisPlayersTurn);

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API APCGame : public APlayerController
{
	GENERATED_BODY()
public:
	APCGame();

	virtual void BeginPlay() override;

protected:
	////////// Player Joining Game //////////

	/**
	* Called when this player controller is ready, calls the game mode to let it know
	*/
	UFUNCTION(Server, Reliable)
	void Server_ReadyToStart();
	////////// Player Joining Game //////////

public:
	void OnTurnChange(bool bThisPlayersTurn);
	
	UPROPERTY(BlueprintReadWrite, Category=Event)
	FOnTurnChange OnTurnChangeEvent;
};
