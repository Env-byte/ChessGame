// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TileController.h"

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

	for (int32 Col = 0; Col < Cols; Col++)
	{
		for (int32 Row = 0; Row < Rows; Row++)
		{
			const ETeams Team = Row == 0 || Row == 1 ? ETeams::Red : Row == 6 || Row == 7 ? ETeams::Blue : ETeams::Neutral;
			const ETileColour Colour = (Row + Col + 1) % 2 == 0 ? ETileColour::White : ETileColour::Black;
			
			if (ATile* Tile = ATile::StartSpawnActor(this, TileClass); Tile != nullptr)
			{
				Tile->Team = Team;
				Tile->TileColour = Colour;
				Tile->TileController = this;

				FTransform Transform;
				Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
				Transform.SetLocation(FVector(Width * Col, Width * Row, 0.f));
				Tile->FinishSpawn(Transform);
			}
		}
	}
}

void ATileController::GenerateTilesDefer()
{
	GetWorld()->GetTimerManager().SetTimer<ATileController>(
		ColHandle,
		this,
		&ATileController::HandleCol,
		Timer * Rows + 0.1f,
		true,
		0.f
	);
}


void ATileController::HandleCol()
{
	CurrentRow = 0;
	GetWorld()->GetTimerManager().SetTimer<ATileController>(
		RowHandle,
		this,
		&ATileController::HandleRow,
		Timer,
		true,
		Timer
	);
}

void ATileController::HandleRow()
{
	const ETeams Team = CurrentRow == 0 || CurrentRow == 1 ? ETeams::Red : CurrentRow == 6 || CurrentRow == 7 ? ETeams::Blue : ETeams::Neutral;
	const ETileColour Colour = (CurrentRow + CurrentCol + 1) % 2 == 0 ? ETileColour::White : ETileColour::Black;
	
	if (ATile* Tile = ATile::StartSpawnActor(this, TileClass); Tile != nullptr)
	{
		Tile->Team = Team;
		Tile->TileColour = Colour;
		Tile->TileController = this;

		FTransform Transform;
		Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
		Transform.SetLocation(FVector(Width * CurrentCol, Width * CurrentRow, 0.f));
		Tile->FinishSpawn(Transform);
	}

	CurrentRow++;
	if (CurrentRow == Rows)
	{
		GetWorld()->GetTimerManager().ClearTimer(RowHandle);
		CurrentCol++;
		if (CurrentCol == Cols)
		{
			GetWorld()->GetTimerManager().ClearTimer(ColHandle);
		}
	}
}
