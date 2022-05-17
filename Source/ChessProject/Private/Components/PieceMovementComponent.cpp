// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PieceMovementComponent.h"

// Sets default values for this component's properties
UPieceMovementComponent::UPieceMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UPieceMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	if (AActor* ActorAttachedTo = GetOwner()->GetRootComponent()->GetAttachParent()->GetOwner(); IsValid(
		ActorAttachedTo))
	{
		if (const AChessPiece* ChessPiece = Cast<AChessPiece>(ActorAttachedTo); IsValid(ChessPiece))
		{
			Type = ChessPiece->PieceType;
		}
	}

	static const UEnum* EPieceTypesEnumType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPieceTypes"));
	FString Msg = FString::Printf(
		TEXT("/SpawnedActors/ChessPawn/%s"), *EPieceTypesEnumType->GetNameStringByIndex(static_cast<int32>(Type)));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, Msg);
}


// Called every frame
void UPieceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
