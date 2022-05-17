// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/HUDGame.h"
DEFINE_LOG_CATEGORY(LogHUDGame);

void AHUDGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif

	if (GameEventClass)
	{
		GameEventText = CreateWidget<UGameEventText>(
			GetOwningPlayerController(),
			GameEventClass,
			FName(TEXT("GameEventText"))
		);
		GameEventText->AddToViewport(1);
	}
	else
	{
		UE_LOG(LogHUDGame, Warning, TEXT("Widget GameEventClass not set"))
	}
	if (GameOverviewClass)
	{
		GameOverview = CreateWidget<UGameOverview>(
			GetOwningPlayerController(),
			GameOverviewClass,
			FName(TEXT("GameOverview"))
		);
		GameOverview->AddToViewport(1);
	}
	else
	{
		UE_LOG(LogHUDGame, Warning, TEXT("Widget GameOverviewClass not set"))
	}
}
