// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "World/ChessPiece.h"
#include "PieceMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHESSPROJECT_API UPieceMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPieceMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The type of piece this determines the movement available
	UPROPERTY(EditDefaultsOnly,Category=Type)
	EPieceTypes Type;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void ShowMoves();
	
	void HideMoves();
};
