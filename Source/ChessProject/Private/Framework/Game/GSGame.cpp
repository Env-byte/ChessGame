// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GSGame.h"

#include "Framework/Game/PCGame.h"
#include "Framework/Game/PSGame.h"
#include "Net/UnrealNetwork.h"

void AGSGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGSGame, PlayerTurn)
}

void AGSGame::SetPlayerTurn(const FPlayerInfo& PlayerInfo)
{
	//if this is called on client return instantly 
	if (!HasAuthority()) { return; }

	PlayerTurn = PlayerInfo.Team;

	// check if the current players turn is the local player as this game is peer to peer not dedicated server
	if (PlayerInfo.PlayerController->IsLocalController())
	{
		//if it is the local controller we manually call on the OnRep_PlayerTurn
		OnRep_PlayerTurn();
	}
}

void AGSGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif
}

void AGSGame::OnRep_PlayerTurn()
{
	// its usually really bad to not check pointers are valid, but if this ever happens then there is a major issue
	APCGame* PC = Cast<APCGame>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (const APSGame* PS = PC->GetPlayerState<APSGame>())
	{
		PC->OnTurnChange(PS->PlayerInfo.Team == PlayerTurn);
	}
}
