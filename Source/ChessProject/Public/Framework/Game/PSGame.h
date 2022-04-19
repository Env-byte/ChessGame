// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GMGame.h"
#include "GameFramework/PlayerState.h"
#include "PSGame.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API APSGame : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Replicated)
	FPlayerInfo PlayerInfo;
};
