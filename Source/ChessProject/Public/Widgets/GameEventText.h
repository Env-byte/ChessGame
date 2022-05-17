// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "GameEventText.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHESSPROJECT_API UGameEventText : public UBaseWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
protected:

	UFUNCTION()
	void HandleTurnChange(bool bIsThisTurn);
	
	UFUNCTION(BlueprintImplementableEvent)
	void DisplayEventMessage(const FText& Message, FColor Color);
};
