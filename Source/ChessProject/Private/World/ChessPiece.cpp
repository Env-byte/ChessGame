// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ChessPiece.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AChessPiece::AChessPiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ChessPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChessPieceMesh");
	PivotOffsetComponent = CreateDefaultSubobject<USceneComponent>("PivotOffset");
	SetRootComponent(PivotOffsetComponent);
	ChessPieceMesh->SetupAttachment(PivotOffsetComponent);
	bReplicates = true;
	SetHidden(true);
}

void AChessPiece::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AChessPiece, Team);
	DOREPLIFETIME(AChessPiece, PieceType);
}

AChessPiece* AChessPiece::StartSpawnActor(const AActor* Owner, const TSubclassOf<AChessPiece> ChessPawnClass)
{
	const UWorld* World = Owner->GetWorld();
	const FTransform Transform = {};

	AActor* Actor = UGameplayStatics::BeginDeferredActorSpawnFromClass(
		World,
		ChessPawnClass,
		Transform,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (Actor == nullptr)
	{
		return nullptr;
	}

	AChessPiece* ChessPawn = Cast<AChessPiece>(Actor);

	return ChessPawn;
}

void AChessPiece::FinishSpawn(const FTransform& Transform)
{
	UGameplayStatics::FinishSpawningActor(this, Transform);

}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	SetHidden(false);
#if WITH_EDITOR
	static const UEnum* EPieceTypesEnumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPieceTypes"));
	SetFolderPath(FName(FString::Printf(
		TEXT("/SpawnedActors/ChessPawn/%s"),
		*EPieceTypesEnumType->GetNameStringByIndex(static_cast<int32>(this->PieceType)))));
#endif
}

void AChessPiece::OnRep_Team()
{
}

void AChessPiece::OnRep_PieceType()
{
}
