// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPawn.generated.h"

UCLASS()
class CHESSPROJECT_API AChessPawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
