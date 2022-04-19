// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GMGame.h"

#include "ChessProject/ChessProject.h"
#include "Framework/Game/PCGame.h"
#include "Framework/Game/PSGame.h"

FPlayerInfo AGMGame::GetConnectedPlayer(const ETeams Team)
{
	if (ConnectedPlayers[0].Team == Team)
	{
		return ConnectedPlayers[0];
	}
	return ConnectedPlayers[1];
}

void AGMGame::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (APCGame* ClientController = Cast<APCGame>(NewPlayer); ClientController != nullptr)
	{
		HandlePlayerJoin(ClientController);
	}
}

void AGMGame::InitSeamlessTravelPlayer(AController* NewController)
{
	Super::InitSeamlessTravelPlayer(NewController);
	if (APCGame* ClientController = Cast<APCGame>(NewController); ClientController != nullptr)
	{
		HandlePlayerJoin(ClientController);
	}
}

void AGMGame::HandlePlayerJoin(APCGame* PlayerController)
{
	APSGame* PS = PlayerController->GetPlayerState<APSGame>();

	if (ConnectedPlayers.Num() == 0)
	{
		PS->PlayerInfo = FPlayerInfo(PlayerController, ETeams::Blue, FMath::RandBool());
	}
	else
	{
		PS->PlayerInfo = FPlayerInfo(PlayerController, ETeams::Red, !ConnectedPlayers[0].bIsFirst);
	}

	ConnectedPlayers.Push(PS->PlayerInfo);

	//start match if it has not already started
	if (!HasMatchStarted())
	{
		//StartMatch();
	}
}

void AGMGame::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}
