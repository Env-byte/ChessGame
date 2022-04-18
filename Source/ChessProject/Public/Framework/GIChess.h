// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "World/ChessPiece.h"
#include "GIChess.generated.h"

/**
 * 
 */
UCLASS()
class CHESSPROJECT_API UGIChess : public UGameInstance
{
	GENERATED_BODY()

protected:
	/**
	 * Set Reference to Chess Pawns Objects here
	 * This is set in Blueprint on the BP_GIChess class
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ChessPawns")
	TMap<EPieceTypes, TSubclassOf<AChessPiece>> ChessPawnClasses;
public:
	/**
	 * Get Chess Pawn Objects
	 * Returns true if found false if not
	 */
	UFUNCTION(BlueprintCallable, Category="ChessPawns")
	bool GetChessPawnClass(const EPieceTypes Piece, TSubclassOf<AChessPiece>& ClassOut);
};
