// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TileController.h"

#include "Framework/GIChess.h"
#include "Framework/Game/GMGame.h"
#include "Framework/Game/PCGame.h"
#include "Net/UnrealNetwork.h"
#include "World/ChessPiece.h"
#include "World/Tile.h"

// Sets default values
ATileController::ATileController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ATileController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATileController, Tiles);
}

// Called when the game starts or when spawned
void ATileController::BeginPlay()
{
	Super::BeginPlay();
}

AChessPiece* ATileController::GetChessPiece(const APCGame* PlayerController, const int32 Col, const int32 Row)
{
	if (UGIChess* GameInstance = GWorld->GetGameInstance<UGIChess>(); GameInstance)
	{
		//this will only happen on server
		//this will replicate down to clients
		EPieceTypes Type = EPieceTypes::None;
		TSubclassOf<AChessPiece> PieceClass = nullptr;
		if (Row == 0 || Row == 7)
		{
			if (Col == 0 || Col == 7)
			{
				Type = EPieceTypes::Rook;
			}
			if (Col == 1 || Col == 6)
			{
				Type = EPieceTypes::Knight;
			}
			if (Col == 2 || Col == 5)
			{
				Type = EPieceTypes::Bishop;
			}
			if (Col == 3)
			{
				Type = EPieceTypes::King;
			}
			if (Col == 4)
			{
				Type = EPieceTypes::Queen;
			}
		}
		else if (Row == 1 || Row == 6)
		{
			Type = EPieceTypes::Pawn;
		}

		if (Type != EPieceTypes::None && GameInstance->GetChessPawnClass(Type, PieceClass))
		{
			return AChessPiece::StartSpawnActor(PlayerController, PieceClass);
		}
	}
	return nullptr;
}

void ATileController::GenerateTiles()
{
	if (!HasAuthority()) { return; }
	if (!TileControllerSettings.TileClass)
	{
		return;
	}
	if (ControllerState != NotStarted)
	{
		return;
	}
	ControllerState = Started;


	for (int32 Row = 0; Row < TileControllerSettings.Rows; Row++)
	{
		Tiles.Add(FTile2DArray());
		for (int32 Col = 0; Col < TileControllerSettings.Cols; Col++)
		{
			GenerateTile(Col, Row);
		}
	}
	ControllerState = Finished;
}

ATile* ATileController::GetTile(const int32 Row, const int32 Col)
{
	if (Tiles.IsValidIndex(Row) && Tiles[Row].Ar.IsValidIndex(Col))
	{
		return Tiles[Row][Col];
	}
	return nullptr;
}

void ATileController::GenerateTile(const int32 Col, const int32 Row)
{
	AGMGame* GameMode = GetWorld()->GetAuthGameMode<AGMGame>();
	if (!IsValid(GameMode))
	{
		return;
	}

	const ETeams Team = Row == 0 || Row == 1
		                    ? ETeams::Red
		                    : Row == TileControllerSettings.Rows - 2 || Row == TileControllerSettings.Rows - 1
		                    ? ETeams::Blue
		                    : ETeams::None;
	const ETileColour Colour = (Row + Col + 1) % 2 == 0 ? ETileColour::White : ETileColour::Black;

	AChessPiece* ChessPiece = nullptr;
	if (Team != ETeams::None)
	{
		//get chess piece and set the player controller as the owner of it for networking purposes

		APSGame* PS = GameMode->GetConnectedPlayer(Team);
		ChessPiece = GetChessPiece(
			PS->PlayerInfo.PlayerController,
			Col,
			Row
		);
		PS->PlayerInfo.ChessPieces.Add(ChessPiece);
	}

	if (ATile* Tile = ATile::StartSpawnActor(this, TileControllerSettings.TileClass); Tile != nullptr)
	{
		Tile->TileInfo = FTileInfo{Col, Row, Colour, Team};
		Tile->TileController = this;

		FTransform Transform;

		Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
		Transform.SetLocation(FVector(TileControllerSettings.Width * Col,
		                              TileControllerSettings.Width * Row, 0.f));
		Tile->FinishSpawn(Transform);

		Tiles[Row].Add(Tile);

		if (ChessPiece && HasAuthority())
		{
			//this will only happen on server
			//this will replicate down to clients 
			Tile->SetChessPiece(ChessPiece);
			ChessPiece->Team = Team;
			Transform.SetRotation(Row == 0 || Row == 1
				                      ? FQuat(0.f, 0.f, 180.f, 0.f)
				                      : FQuat(0.f, 0.f, 0.f, 0.f));
			Transform.SetLocation(FVector(TileControllerSettings.Width * Col,
			                              TileControllerSettings.Width * Row, 50.f));
			ChessPiece->FinishSpawn(Transform);
		}
	}
}
