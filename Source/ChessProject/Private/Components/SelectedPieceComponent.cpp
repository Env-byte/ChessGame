// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SelectedPieceComponent.h"

#include "UObject/ConstructorHelpers.h"

USelectedPieceComponent::USelectedPieceComponent()
{
	SetRelativeRotation(FRotator::ZeroRotator);
	// set widget class to our Blueprinted widget class
	if (static ConstructorHelpers::FClassFinder<UUserWidget> WidgetComponentBPClass(
		TEXT("/Game/Widget/Components/BPW_SelectedPiece")); WidgetComponentBPClass.Class != nullptr)
	{
		WidgetClass = WidgetComponentBPClass.Class;
	}
	Space = EWidgetSpace::Screen;
	bDrawAtDesiredSize = true;
	bAutoActivate = false;
}

void USelectedPieceComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}


void USelectedPieceComponent::Show()
{
	Activate();
	if (GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void USelectedPieceComponent::Hide()
{
	Deactivate();
	if (GetWidget())
	{
		GetWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}
