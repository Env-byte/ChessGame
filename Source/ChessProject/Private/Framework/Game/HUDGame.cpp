// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/HUDGame.h"

void AHUDGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/Framework"))));
#endif
}
