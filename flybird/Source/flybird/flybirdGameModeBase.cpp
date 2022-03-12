// Copyright Epic Games, Inc. All Rights Reserved.


#include "flybirdGameModeBase.h"

#include "Public/BirdGameStateBase.h"
#include "Public/BirdPawn.h"
#include "Public/BgActor.h"
#include "Public/LandActor.h"
#include "Public/PipeActor.h"

AflybirdGameModeBase::AflybirdGameModeBase()
{
	//游戏视角默认为:ABirdPawn
	DefaultPawnClass = ABirdPawn::StaticClass();
	//游戏状态配置为:ABirdGameModeBase
	GameStateClass = ABirdGameStateBase::StaticClass();
}
//起始位置
void AflybirdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//地图中加载资源
	GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(),FVector(0.0f,-100.0f,0.0f),FRotator::ZeroRotator);

	GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(), FVector(0.0f, 0.0f,-270.0f), FRotator::ZeroRotator);

	GetWorld()->SpawnActor<APipeActor>(APipeActor::StaticClass(), FVector(200.0f, 0.0f, 0.0f), FRotator::ZeroRotator);

}

