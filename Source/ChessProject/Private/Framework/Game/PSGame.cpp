// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PSGame.h"

#include "Net/UnrealNetwork.h"

void APSGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSGame, PlayerInfo);
}

void APSGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif
}
