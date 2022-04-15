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

void ATileController::GenerateTilesDefer()
{
	GenerateTiles();
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
				Timer * Rows + 0.1f,
				true,
				0.f
			);
		}
	}
}

void ATileController::GenerateTile()
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

	CurrentRow += 1;

	if (CurrentRow == Rows)
	{
		CurrentCol += 1;
		CurrentRow = 0;
		
		if (CurrentCol == Cols)
		{
			GetWorld()->GetTimerManager().ClearTimer(Handle);
		}
	}
}