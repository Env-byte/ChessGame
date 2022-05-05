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

#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif
}

void APCGame::OnTurnChange(const bool bThisPlayersTurn)
{

	
	if (bThisPlayersTurn)
	{
		EnableInput(this);
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Its Your Turn")));
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
