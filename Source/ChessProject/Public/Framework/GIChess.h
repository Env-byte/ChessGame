// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "World/ChessPawn.h"
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
	TArray<AChessPawn*> ChessPawns;
public:
	/**
	 * Get Chess Pawn Objects
	 */
	UFUNCTION(BlueprintCallable, Category="ChessPawns")
	FORCEINLINE TArray<AChessPawn*> GetChessPawns() const { return ChessPawns; }
};
