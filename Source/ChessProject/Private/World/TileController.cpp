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
	
	ETileColour Colour = ETileColour::White;
	for (int32 Col = 0; Col < Cols; Col++)
	{
		if (Colour == ETileColour::White)
		{
			Colour = ETileColour::Black;
		}
		else
		{
			Colour = ETileColour::White;
		}
		for (int32 Row = 0; Row < Rows; Row++)
		{
			ETeams Team = ETeams::Neutral;
			if (Colour == ETileColour::White)
			{
				Colour = ETileColour::Black;
			}
			else
			{
				Colour = ETileColour::White;
			}
			if (Row == 0 || Row == 1)
			{
				Team = ETeams::Red;
			}
			if (Row == 7 || Row == 8)
			{
				Team = ETeams::Blue;
			}
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
