// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SelectedPieceComponent.h"

#include "UObject/ConstructorHelpers.h"

USelectedPieceComponent::USelectedPieceComponent()
{
	SetRelativeRotation(FRotator::ZeroRotator);
	// set widget class to our Blueprinted widget class
	if (static ConstructorHelpers::FClassFinder<UUserWidget> WidgetComponentBPClass(
		TEXT("/Game/Blueprints/Widgets/Components/BPW_SelectedPiece")); WidgetComponentBPClass.Class != nullptr)
	{
		WidgetClass = WidgetComponentBPClass.Class;
	}
	Space = EWidgetSpace::Screen;
	bDrawAtDesiredSize = true;
}

void USelectedPieceComponent::Show()
{
}

void USelectedPieceComponent::Hide()
{
}
