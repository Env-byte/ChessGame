// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ChessPawn.h"

// Sets default values
AChessPawn::AChessPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ChessPieceMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChessPieceMesh");
	SetRootComponent(ChessPieceMesh);
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AChessPawn::BeginPlay()
{
	Super::BeginPlay();
	
}
