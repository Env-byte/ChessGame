// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GMGame.h"

#include "Editor.h"
#include "ChessProject/ChessProject.h"
#include "Framework/Game/GSGame.h"
#include "Framework/Game/PCGame.h"
#include "Framework/Game/PSGame.h"
#include "Kismet/GameplayStatics.h"
#include "World/SpawnController.h"
#include "World/TileController.h"


APSGame* AGMGame::GetConnectedPlayer(const ETeams Team)
{
	if (ConnectedPlayers[0]->PlayerInfo.Team == Team)
	{
		return ConnectedPlayers[0];
	}
	//this is only false in play in editor with only one instance
	if (ConnectedPlayers.IsValidIndex(1) && ConnectedPlayers[1])
	{
		return ConnectedPlayers[1];
	}
	return nullptr;
}

void AGMGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif
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

	FPlayerInfo PlayerInfo;
	if (ConnectedPlayers.Num() == 0)
	{
		PlayerInfo = FPlayerInfo(PlayerController, ETeams::Blue, FMath::RandBool());
	}
	else
	{
		PlayerInfo = FPlayerInfo(PlayerController, ETeams::Red, !ConnectedPlayers[0]->PlayerInfo.bIsFirst);
	}
	PS->PlayerInfo = PlayerInfo;
	ConnectedPlayers.Add(PS);
	//start match if it has not already started
	if (!HasMatchStarted())
	{
		StartMatch();
	}
}

void AGMGame::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AGMGame::PlayerControllerReady()
{
	ReadyPlayers++;
	int32 NumPIEClients = 0;
	//make sure game can start with only one client on play instance editor
#if WITH_EDITOR
	if (GEditor && GEditor->IsPlaySessionRequestQueued())
	{
		GEditor->GetPlaySessionRequest()->EditorPlaySettings->GetPlayNumberOfClients(NumPIEClients);
	}
	else if (GEditor && GEditor->IsPlaySessionInProgress())
	{
		NumPIEClients = GEditor->GetPlayInEditorSessionInfo()->PIEInstanceCount;
	}
#endif


	if (ReadyPlayers == 2 || NumPIEClients == ReadyPlayers)
	{
		//start game loop here
		if (ATileController* TileController = ATileController::Get(GetWorld()); IsValid(TileController))
		{
			TileController->GenerateTiles();

			if (const ASpawnController* SpawnController = ASpawnController::Get(GetWorld()); IsValid(SpawnController))
			{
				PlayerSpawns = SpawnController->GenerateSpawns(TileController);
			}
		}


		for (const APSGame* ConnectedPlayer : ConnectedPlayers)
		{
			BP_SpawnPlayerCamera(ConnectedPlayer->PlayerInfo);
			if (ConnectedPlayer->PlayerInfo.bIsFirst)
			{
				GetGameState<AGSGame>()->SetPlayerTurn(ConnectedPlayer->PlayerInfo);
			}
		}
	}
}
