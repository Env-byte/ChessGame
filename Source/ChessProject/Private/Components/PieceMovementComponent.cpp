// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PieceMovementComponent.h"

#include "ComponentUtils.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = false;
}


// Called when the game starts
void UPieceMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* ActorAttachedTo = GetOwner(); IsValid(ActorAttachedTo))
	{
		if (const AChessPiece* ChessPiece = Cast<AChessPiece>(ActorAttachedTo); IsValid(ChessPiece))
		{
			Type = ChessPiece->PieceType;
		}
	}
}


void UPieceMovementComponent::ShowMoves()
{
	Activate();
}

void UPieceMovementComponent::HideMoves()
{
	Deactivate();
}
