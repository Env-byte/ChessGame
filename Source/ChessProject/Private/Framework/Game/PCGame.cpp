// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PCGame.h"

#include "Framework/Game/GMGame.h"
#include "World/ChessPiece.h"

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

void APCGame::OnSelect()
{
	FHitResult HitResult;

	const ECollisionChannel SelectedChannel = UEngineTypes::ConvertToCollisionChannel(TraceTypeQuery15);
	const FString ResourceString = StaticEnum<ECollisionChannel>()->GetValueAsString(SelectedChannel);

	//TraceTypeQuery15 is my custom channel SelectTrace which is block all
	if (!GetHitResultUnderCursorByChannel(TraceTypeQuery15, true, HitResult))
	{
		return;
	}
	if (!IsValid(HitResult.GetActor()))
	{
		return;
	}

	if (AChessPiece* ChessPiece = Cast<AChessPiece>(HitResult.GetActor()); IsValid(ChessPiece))
	{
		if (APSGame* PSGame = GetPlayerState<APSGame>(); ChessPiece->Team == PSGame->PlayerInfo.Team)
		{
			PSGame->SetSelectedPiece(ChessPiece);
		}
	}
}

void APCGame::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &APCGame::OnSelect);
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
	OnTurnChangeEvent.Broadcast(bThisPlayersTurn);
}

void APCGame::Server_ReadyToStart_Implementation()
{
	if (AGMGame* GameMode = GetWorld()->GetAuthGameMode<AGMGame>())
	{
		GameMode->PlayerControllerReady();
	}
}
