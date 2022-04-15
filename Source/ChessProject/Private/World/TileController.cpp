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
	GEngine->AddOnScreenDebugMessage(
		-1,
		1.f,
		FColor::Red,
		FString::Printf(TEXT("Col:%d, Row:%d"), Cols, Rows)
	);
	for (int32 Row = 0; Row < Rows; Row++)
	{
		for (int32 Col = 0; Col < Cols; Col++)
		{
			ETileColour Colour = ETileColour::White;
			ETeams Team = ETeams::Neutral;
			if (Row % 2 == 0)
			{
				Colour = ETileColour::Black;
			}
			if (Row == 0 || Row == 1)
			{
				Team = ETeams::Red;
			}
			if (Row == 7 || Row == 8)
			{
				Team = ETeams::Blue;
			}
			if (ATile* Tile = ATile::StartSpawnActor(); IsValid(Tile))
			{
				Tile->Team = Team;
				Tile->TileColour = Colour;
				FTransform Transform;
				Transform.SetRotation(FQuat(0.f, 0.f, 0.f, 0.f));
				Transform.SetLocation(FVector(Tile->Width * Col, Tile->Width * Row, 0.f));
				Tile->FinishSpawn(Transform);
			}
		}
	}
}
