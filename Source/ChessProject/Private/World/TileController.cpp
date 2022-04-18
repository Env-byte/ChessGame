// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TileController.h"

#include "Framework/GIChess.h"
#include "World/ChessPiece.h"
#include "World/Tile.h"

// Sets default values
ATileController::ATileController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATileController::BeginPlay()
{
	Super::BeginPlay();
}

void ATileController::GenerateTiles()
{
	if (!TileClass)
	{
		return;
	}

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	for (int32 Col = 0; Col < Cols; Col++)
	{
		for (int32 Row = 0; Row < Rows; Row++)
		{
			TimerManager.SetTimer<ATileController>(
				Handle,
				this,
				&ATileController::GenerateTile,
				(Row + 1) * (Col + 1) * TimerScale,
				true,
				0.f
			);
		}
	}
}

AChessPiece* ATileController::GetChessPiece()
{
	if (UGIChess* GameInstance = GWorld->GetGameInstance<UGIChess>(); GameInstance && HasAuthority())
	{
		//this will only happen on server
		//this will replicate down to clients
		EPieceTypes Type = EPieceTypes::None;
		TSubclassOf<AChessPiece> PieceClass = nullptr;
		if (CurrentRow == 0 || CurrentRow == 7)
		{
			if (CurrentCol == 0 || CurrentCol == 7)
			{
				Type = EPieceTypes::Rook;
			}
			if (CurrentCol == 1 || CurrentCol == 6)
			{
				Type = EPieceTypes::Knight;
			}
			if (CurrentCol == 2 || CurrentCol == 5)
			{
				Type = EPieceTypes::Bishop;
			}
			if (CurrentCol == 3)
			{
				Type = EPieceTypes::King;
			}
			if (CurrentCol == 4)
			{
				Type = EPieceTypes::Queen;
			}
		}
		else if (CurrentRow == 1 || CurrentRow == 6)
		{
			Type = EPieceTypes::Pawn;
		}

		if (Type != EPieceTypes::None && GameInstance->GetChessPawnClass(Type, PieceClass))
		{
			return AChessPiece::StartSpawnActor(this, PieceClass);
		}
	}
	return nullptr;
}

void ATileController::GenerateTile()
{
	// todo probably need to replace the owners of the piece and tile to
	// be the player controller for networking to work correctly

	const ETeams Team = CurrentRow == 0 || CurrentRow == 1
		                    ? ETeams::Red
		                    : CurrentRow == 6 || CurrentRow == 7
		                    ? ETeams::Blue
		                    : ETeams::Neutral;
	const ETileColour Colour = (CurrentRow + CurrentCol + 1) % 2 == 0 ? ETileColour::White : ETileColour::Black;

	AChessPiece* ChessPiece = GetChessPiece();

	if (ATile* Tile = ATile::StartSpawnActor(this, TileClass); Tile != nullptr)
	{
		Tile->Team = Team;
		Tile->TileColour = Colour;
		Tile->TileController = this;

		FTransform Transform;

		Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
		Transform.SetLocation(FVector(Width * CurrentCol, Width * CurrentRow, 0.f));
		Tile->FinishSpawn(Transform);

		if (ChessPiece && HasAuthority())
		{
			//this will only happen on server
			//this will replicate down to clients 
			Tile->SetChessPiece(ChessPiece);
			ChessPiece->Team = Team;
			Transform.SetRotation(CurrentRow == 0 || CurrentRow == 1
				                      ? FQuat(0.f, 0.f, 180.f, 0.f)
				                      : FQuat(0.f, 0.f, 0.f, 0.f));
			Transform.SetLocation(FVector(Width * CurrentCol, Width * CurrentRow, 50.f));
			ChessPiece->FinishSpawn(Transform);
		}
	}

	CurrentRow += 1;

	if (CurrentRow == Rows)
	{
		CurrentCol += 1;
		CurrentRow = 0;

		if (CurrentCol == Cols)
		{
			GetWorld()->GetTimerManager().ClearTimer(Handle);
			bIsLoaded = true;
		}
	}
}
