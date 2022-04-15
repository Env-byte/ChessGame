// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Tile.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

void ATile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATile, ChessPawn);
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
}

void ATile::OnRep_ChessPawn()
{
	//can be used to correct incorrect changes to the game. such as the piece moving on client when its not valid on server
}

void ATile::SetChessPawn(AChessPawn* Pawn)
{
	if (!Pawn->HasAuthority())
	{
		//this is client
		Server_SetChessPawn(Pawn);
		// we do not return as we want changes to happen simultaneously between client / server
		// otherwise it would give the impression of lag
		
	}else
	{
		//this is server
		//we can validated the move here and correct inconsistency using OnRep_ChessPawn
	}
	ChessPawn = Pawn;

	
}

void ATile::Server_SetChessPawn_Implementation(AChessPawn* Pawn)
{
	SetChessPawn(Pawn);
}
