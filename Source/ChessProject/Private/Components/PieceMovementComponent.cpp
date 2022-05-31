// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PieceMovementComponent.h"

#include "ComponentUtils.h"
#include "World/TileController.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = false;
}


// Called when the game starts
void UPieceMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* ActorAttachedTo = GetOwner(); IsValid(ActorAttachedTo))
	{
		if (AChessPiece* AttachedChessPiece = Cast<AChessPiece>(ActorAttachedTo); IsValid(AttachedChessPiece))
		{
			this->ChessPiece = AttachedChessPiece;
		}
	}
}


void UPieceMovementComponent::ShowMoves()
{
	ATileController* TileController = ATileController::Get(GetWorld());

	if (!IsValid(TileController))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString(TEXT("!IsValid(TileController)")));
		return;
	}
	if (!IsValid(ChessPiece))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString(TEXT("!IsValid(ChessPiece)")));
		return;
	}
	Activate();
	HideMoves();

	const FTileInfo CurrentTile = ChessPiece->Tile->TileInfo;

	switch (ChessPiece->PieceType)
	{
	case EPieceTypes::None:

		break;
	case EPieceTypes::Knight:
		KnightMoves(CurrentTile, TileController);
		break;
	case EPieceTypes::Pawn:
		PawnMoves(CurrentTile, TileController);
		break;
	case EPieceTypes::Queen:
		QueenMoves(CurrentTile, TileController);
		break;
	case EPieceTypes::King:
		KingMoves(CurrentTile, TileController);
		break;
	case EPieceTypes::Rook:
		RookMoves(CurrentTile, TileController);
		break;
	case EPieceTypes::Bishop:
		BishopMoves(CurrentTile, TileController);
		break;
	}

	for (ATile* Tile : PossibleMoves)
	{
		Tile->BP_AddHighlight();
	}
}

void UPieceMovementComponent::HideMoves()
{
	for (ATile* Tile : PossibleMoves)
	{
		Tile->BP_RemoveHighlight();
	}
	PossibleMoves.Empty();
	Deactivate();
}

void UPieceMovementComponent::BishopMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	ATile* Tile;
	for (int32 i = 0; i < 4; i++)
	{
		int32 Col = CurrentTile.Col;
		int32 Row = CurrentTile.Row;
		do
		{
			switch (i)
			{
			case 0:
				Col++;
				Row++;
				break;
			case 1:
				Col--;
				Row--;
				break;
			case 2:
				Col++;
				Row--;
				break;
			case 3:
				Col--;
				Row++;
				break;
			default: break;
			}
			Tile = TileController->GetTile(Row, Col);
			if (IsValid(Tile))
			{
				PossibleMoves.Add(Tile);
			}
		}
		while (IsValid(Tile));
	}
}

void UPieceMovementComponent::RookMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	ATile* Tile;
	for (int32 i = 0; i < 4; i++)
	{
		int32 Col = CurrentTile.Col;
		int32 Row = CurrentTile.Row;
		do
		{
			switch (i)
			{
			case 0:
				Col++;
				break;
			case 1:
				Col--;
				break;
			case 2:
				Row--;
				break;
			case 3:
				Row++;
				break;
			default: break;
			}
			Tile = TileController->GetTile(Row, Col);
			if (IsValid(Tile))
			{
				PossibleMoves.Add(Tile);
			}
		}
		while (IsValid(Tile));
	}
}

void UPieceMovementComponent::KingMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	for (int32 i = 0; i < 8; i++)
	{
		int32 Col = CurrentTile.Col;
		int32 Row = CurrentTile.Row;
		switch (i)
		{
		case 0:
			Col++;
			break;
		case 1:
			Col--;
			break;
		case 2:
			Row--;
			break;
		case 3:
			Row++;
			break;
		case 4:
			Col++;
			Row++;
			break;
		case 5:
			Col--;
			Row--;
			break;
		case 6:
			Col++;
			Row--;
			break;
		case 7:
			Col--;
			Row++;
			break;
		default: break;
		}
		if (ATile* Tile = TileController->GetTile(Row, Col); IsValid(Tile))
		{
			PossibleMoves.Add(Tile);
		}
	}
}

void UPieceMovementComponent::QueenMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	//queen is combination of rook and bishop
	RookMoves(CurrentTile, TileController);
	BishopMoves(CurrentTile, TileController);
}

void UPieceMovementComponent::PawnMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	const int32 Col = CurrentTile.Col;
	const int32 Row = CurrentTile.Row;
	const bool bIsBlue = ChessPiece->Team == ETeams::Blue;
	ATile* Tile = TileController->GetTile(bIsBlue ? Row - 1 : Row + 1, Col);
	if (IsValid(Tile))
	{
		PossibleMoves.Add(Tile);
	}
	if (ChessPiece->GetTimesMoved() == 0)
	{
		Tile = TileController->GetTile(bIsBlue ? Row - 2 : Row + 2, Col);
		if (IsValid(Tile))
		{
			PossibleMoves.Add(Tile);
		}
	}
}

void UPieceMovementComponent::KnightMoves(const FTileInfo CurrentTile, ATileController* TileController)
{
	bool bVertical = false;

	for (int32 i = 0; i < 4; i++)
	{
		int32 Col = CurrentTile.Col;
		int32 Row = CurrentTile.Row;
		switch (i)
		{
		case 0:
			Row = Row - 2;
			bVertical = true;
			break;
		case 1:
			Row = Row + 2;
			bVertical = true;
			break;
		case 2:
			Col = Col + 2;
			bVertical = false;
			break;
		case 3:
			Col = Col - 2;
			bVertical = false;
			break;
		default: ;
		}
		for (int X = 0; X < 2; X++)
		{
			int32 Op = 0;
			if (X == 0)
			{
				Op = + 1;
			}
			else
			{
				Op = -1;
			}

			if (ATile* Tile = TileController->GetTile(bVertical ? Row : Row + Op, bVertical ? Col + Op : Col);
				IsValid(Tile))
			{
				PossibleMoves.Add(Tile);
			}
		}
	}
}
