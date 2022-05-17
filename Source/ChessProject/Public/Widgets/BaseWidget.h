// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

class APCGame;
/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class CHESSPROJECT_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly)
	APCGame* PlayerControllerRef;
};
