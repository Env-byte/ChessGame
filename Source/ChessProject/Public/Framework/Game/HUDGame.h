// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDGame.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AHUDGame : public AHUD
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
};
