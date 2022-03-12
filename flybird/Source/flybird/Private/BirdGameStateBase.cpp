// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdGameStateBase.h"
#include "BirdPawn.h"

ABirdGameStateBase::ABirdGameStateBase()
{
	fSpeed = 1.0f;
	CurrentGameState = EGameState::EGAME_IDLE;
}
void ABirdGameStateBase::AddScore()
{
	if (CurrentGameState != EGameState::EGAME_RUNING) return;

	FString DebugMessage = FString::Printf(TEXT("Score:%d"), iScore++);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage); //3.0f 
	iScore++;
}

int ABirdGameStateBase::GetScore()
{
	return 0;
}

int ABirdGameStateBase::RetsetScore()
{
	return 0;
}

int ABirdGameStateBase::SetGameState(EGameState::EGameState GameState)
{
	CurrentGameState = GameState;
	if (GEngine)
	{	//打印到视口
		FString DebugMessage = FString::Printf(TEXT("SetGameState:%d"), CurrentGameState);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage); //3.0f 
		UE_LOG(LogTemp, Warning, TEXT("%s"),*DebugMessage);
	}
	return 0;
}

EGameState::EGameState ABirdGameStateBase::GetGameState()
{
	return CurrentGameState;
}
