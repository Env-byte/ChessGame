// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/GameEventText.h"
#include "Widgets/GameOverview.h"
#include "HUDGame.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogHUDGame, Log, All);

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API AHUDGame : public AHUD
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

protected:
	/**
	 * Widget setup
	 */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=WidgetClasses)
	TSubclassOf<UGameEventText> GameEventClass;

	UPROPERTY(BlueprintReadOnly, Category=Widgets)
	UGameEventText* GameEventText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=WidgetClasses)
	TSubclassOf<UGameOverview> GameOverviewClass;

	UPROPERTY(BlueprintReadOnly, Category=Widgets)
	UGameOverview* GameOverview;
	/**/
};
