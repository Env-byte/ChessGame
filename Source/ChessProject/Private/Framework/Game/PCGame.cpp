// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PCGame.h"

#include "Framework/Game/GMGame.h"

APCGame::APCGame()
{
}

void APCGame::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalController())
	{
		Server_ReadyToStart();
	}
	DisableInput(this);
}

void APCGame::OnTurnChange(const bool bThisPlayersTurn)
{
	if (bThisPlayersTurn)
	{
		EnableInput(this);
	}
	else
	{
		DisableInput(this);
	}
}

void APCGame::Server_ReadyToStart_Implementation()
{
	if (AGMGame* GameMode = GetWorld()->GetAuthGameMode<AGMGame>())
	{
		GameMode->PlayerControllerReady();
	}
}
