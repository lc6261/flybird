// Copyright Epic Games, Inc. All Rights Reserved.


#include "flybirdGameModeBase.h"

#include "Public/BirdGameStateBase.h"
#include "Public/BirdPawn.h"
#include "Public/BgActor.h"
#include "Public/LandActor.h"
#include "Public/PipeActor.h"

AflybirdGameModeBase::AflybirdGameModeBase()
{
	//��Ϸ�ӽ�Ĭ��Ϊ:ABirdPawn
	DefaultPawnClass = ABirdPawn::StaticClass();
	//��Ϸ״̬����Ϊ:ABirdGameModeBase
	GameStateClass = ABirdGameStateBase::StaticClass();
}
//��ʼλ��
void AflybirdGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	//��ͼ�м�����Դ
	GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(),FVector(0.0f,-100.0f,0.0f),FRotator::ZeroRotator);

	GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(), FVector(0.0f, 0.0f,-270.0f), FRotator::ZeroRotator);

	GetWorld()->SpawnActor<APipeActor>(APipeActor::StaticClass(), FVector(200.0f, 0.0f, 0.0f), FRotator::ZeroRotator);

}

