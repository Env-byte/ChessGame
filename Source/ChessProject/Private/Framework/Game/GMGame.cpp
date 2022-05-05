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


FPlayerInfo AGMGame::GetConnectedPlayer(const ETeams Team)
{
	if (ConnectedPlayers[0].Team == Team)
	{
		return ConnectedPlayers[0];
	}
	//this is only false in play in editor with only one instance
	if (ConnectedPlayers.IsValidIndex(1))
	{
		return ConnectedPlayers[1];
	}
	return ConnectedPlayers[0];
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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("HandlePlayerJoin")));

	FPlayerInfo PlayerInfo;
	if (ConnectedPlayers.Num() == 0)
	{
		PlayerInfo = FPlayerInfo(PlayerController, ETeams::Blue, FMath::RandBool());
	}
	else
	{
		PlayerInfo = FPlayerInfo(PlayerController, ETeams::Red, !ConnectedPlayers[0].bIsFirst);
	}

	ConnectedPlayers.Add(PlayerInfo);
	PS->PlayerInfo = PlayerInfo;
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
	if (GEditor->IsPlaySessionRequestQueued())
	{
		GEditor->GetPlaySessionRequest()->EditorPlaySettings->GetPlayNumberOfClients(NumPIEClients);
	}
	else if (GEditor->IsPlaySessionInProgress())
	{
		NumPIEClients = GEditor->GetPlayInEditorSessionInfo()->PIEInstanceCount;
	}
#endif

	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Yellow,
		FString::Printf(TEXT("PIEInstanceCount : %d"),
		                NumPIEClients
		)
	);

	if (ReadyPlayers == 2 || NumPIEClients == ReadyPlayers)
	{
		//start game loop here

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow,
		                                 FString::Printf(TEXT("ConnectedPlayers : %d"), ConnectedPlayers.Num()));


		TArray<AActor*> OutTileController;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileController::StaticClass(), OutTileController);

		if (OutTileController.Num() > 0)
		{
			if (ATileController* TileController = Cast<ATileController>(OutTileController[0]))
			{
				TileController->GenerateTiles();
				TArray<AActor*> OutSpawnController;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnController::StaticClass(), OutSpawnController);
				if (OutSpawnController.Num() > 0)
				{
					if (ASpawnController* SpawnController = Cast<ASpawnController>(OutSpawnController[0]))
					{
						PlayerSpawns = SpawnController->GenerateSpawns(TileController);
					}
				}
			}
		}

		for (const FPlayerInfo ConnectedPlayer : ConnectedPlayers)
		{
			BP_SpawnPlayerCamera(ConnectedPlayer);
			if (ConnectedPlayer.bIsFirst)
			{
				GetGameState<AGSGame>()->SetPlayerTurn(ConnectedPlayer);
			}
		}
	}
}
