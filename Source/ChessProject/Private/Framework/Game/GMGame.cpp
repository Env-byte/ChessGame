// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GMGame.h"

#include "Editor.h"
#include "ChessProject/ChessProject.h"
#include "Framework/Game/GSGame.h"
#include "Framework/Game/PCGame.h"
#include "Framework/Game/PSGame.h"
#include "Kismet/GameplayStatics.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("HandlePlayerJoin ")));

	if (ConnectedPlayers.Num() == 0)
	{
		PS->PlayerInfo = FPlayerInfo(PlayerController, ETeams::Blue, FMath::RandBool());
	}
	else
	{
		PS->PlayerInfo = FPlayerInfo(PlayerController, ETeams::Red, !ConnectedPlayers[0].bIsFirst);
	}

	SpawnPlayerCamera(PS->PlayerInfo);
	ConnectedPlayers.Push(PS->PlayerInfo);

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
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Black,
		FString::Printf(TEXT("PlayerControllerReady %d. IsPlayingSessionInEditor %s. NumClientInstances %d "),
		                ReadyPlayers,
		                GEditor->IsPlayingSessionInEditor() ? TEXT("TRUE") : TEXT("FALSE"),
		                GEditor->GetPlayInEditorSessionInfo()->PIEInstanceCount
		));
	ReadyPlayers++;

	if (ReadyPlayers == 2 || (GEditor->IsPlayingSessionInEditor() && GEditor->GetPlayInEditorSessionInfo()->
	                                                                          PIEInstanceCount == ReadyPlayers))
	{
		//start game loop here
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileController::StaticClass(), OutActors);

		if (OutActors.Num() > 0)
		{
			if (ATileController* TileController = Cast<ATileController>(OutActors[0]))
			{
				TileController->GenerateTiles();
			}
		}
		for (const FPlayerInfo ConnectedPlayer : ConnectedPlayers)
		{
			if (ConnectedPlayer.bIsFirst)
			{
				GetGameState<AGSGame>()->SetPlayerTurn(ConnectedPlayer);
			}
		}
	}
}
