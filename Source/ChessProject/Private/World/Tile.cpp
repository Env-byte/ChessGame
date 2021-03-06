// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Tile.h"

#include "Framework/Game/GMGame.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "World/ChessPiece.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMesh");
	SetRootComponent(TileMesh);
	bReplicates = true;
	SetHidden(true);
}

void ATile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATile, ChessPiece);
	DOREPLIFETIME(ATile, TileInfo);
	DOREPLIFETIME(ATile, TileController);
	DOREPLIFETIME(ATile, CanMoveTo);
}

void ATile::SetCanMoveTo(const bool bCond)
{
	CanMoveTo = bCond;
}

ATile* ATile::StartSpawnActor(const AActor* Owner, const TSubclassOf<ATile> TileClass)
{
	const UWorld* World = Owner->GetWorld();
	const FTransform Transform = {};

	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(
		World,
		TileClass,
		Transform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (Actor == nullptr)
	{
		return nullptr;
	}

	ATile* Tile = Cast<ATile>(Actor);
	return Tile;
}

void ATile::FinishSpawn(const FTransform& Transform)
{
	UGameplayStatics::FinishSpawningActor(this, Transform);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SetHidden(false);
#if WITH_EDITOR
	SetFolderPath(FName(FString::Printf(TEXT("/SpawnedActors/Tile"))));
#endif
}

void ATile::OnRep_ChessPiece()
{
	//can be used to correct incorrect changes to the game. such as the piece moving on client when its not valid on server
}

void ATile::SetChessPiece(AChessPiece* Pawn)
{
	if (!Pawn->HasAuthority())
	{
		//this is client
		Server_SetChessPiece(Pawn);
		// we do not return as we want changes to happen simultaneously between client / server
		// otherwise it would give the impression of lag
	}
	else
	{
		//this is server
		//we can validated the move here and correct inconsistency using OnRep_ChessPawn
		//let the chess piece know which tile its on
		AGMGame* GM = GetWorld()->GetAuthGameMode<AGMGame>();
		if (CanMoveTo || GM->bGameStarted == false)
		{
			Pawn->Tile = this;
			ChessPiece = Pawn;
			if (GM->bGameStarted)
			{
				ChessPiece->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 50.f));
				GM->ChangeTurns();
			}
		}
	}
}

void ATile::Server_SetChessPiece_Implementation(AChessPiece* Pawn)
{
	SetChessPiece(Pawn);
}
