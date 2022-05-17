// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameEventText.h"

#include "Framework/Game/PCGame.h"

void UGameEventText::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerControllerRef->OnTurnChangeEvent.AddDynamic(this, &UGameEventText::HandleTurnChange);
}

void UGameEventText::HandleTurnChange(bool bIsThisTurn)
{
	const FText Message = bIsThisTurn
		                      ? FText::FromString("It's your turn")
		                      : FText::FromString("It's the other players turn");
	DisplayEventMessage(Message, FColor::Red);
}
