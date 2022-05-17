// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PSGame.h"

#include "Components/PieceMovementComponent.h"
#include "Net/UnrealNetwork.h"

void APSGame::OnRep_SelectedPiece()
{
	for (const AChessPiece* ChessPiece : PlayerInfo.ChessPieces)
	{
		ChessPiece->SelectedPieceComponent->Hide();
		ChessPiece->PieceMovementComponent->HideMoves();
	}
	
	if (IsValid(SelectedPiece))
	{
		SelectedPiece->SelectedPieceComponent->Show();
		//only show piece movement for the local player
		if (IsValid(GetOwningController()))
		{
			SelectedPiece->PieceMovementComponent->ShowMoves();
		}
	}
}

void APSGame::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APSGame, PlayerInfo);
	DOREPLIFETIME(APSGame, SelectedPiece);
}

void APSGame::Server_SetSelectedPiece_Implementation(AChessPiece* ChessPiece)
{
	SetSelectedPiece(ChessPiece);
	//check that the right piece has been selected
	//else deselect the piece
	if (ChessPiece->Team != PlayerInfo.Team)
	{
		SelectedPiece = nullptr;
	}
}

void APSGame::SetSelectedPiece(AChessPiece* ChessPiece)
{
	if (IsValid(ChessPiece))
	{
		SelectedPiece = ChessPiece;
	}
	OnRep_SelectedPiece();
	if (!HasAuthority())
	{
		Server_SetSelectedPiece(ChessPiece);
	}
}

void APSGame::BeginPlay()
{
	Super::BeginPlay();
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Framework"))));
#endif
}
