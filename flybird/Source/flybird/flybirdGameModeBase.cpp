// Copyright Epic Games, Inc. All Rights Reserved.


#include "flybirdGameModeBase.h"
#include "BirdPawn.h"
#include "BgActor.h"
#include "LandActor.h"

AflybirdGameModeBase::AflybirdGameModeBase()
{
	//游戏视角默认为birdpawn
	DefaultPawnClass = ABirdPawn::StaticClass();
}

void AflybirdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(),FVector(0.0f,-10.0f,0.0f),FRotator::ZeroRotator);

	GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(), FVector(0.0f, -9.0f,-280.0f), FRotator::ZeroRotator);

}

