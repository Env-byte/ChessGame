// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SelectedPieceComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API USelectedPieceComponent : public UWidgetComponent
{
	GENERATED_BODY()

	USelectedPieceComponent();
public:
	void Show();
	void Hide();
};
