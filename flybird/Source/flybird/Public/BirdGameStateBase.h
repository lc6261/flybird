// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameStateBase.generated.h"

namespace EGameState
{
	enum EGameState
	{
		EGAME_IDLE,
		EGAME_RUNING,
		EGAME_OVER
	};
}
#define POINT_NULL_RETURN_ZERO(prt) do{if(!(prt)) return 0;}while(0)
#define POINT_NULL_RETURN(prt) do{if(!(prt)) return;}while(0)
/**
 * 
 */
UCLASS()
class FLYBIRD_API ABirdGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	ABirdGameStateBase();
public:
	int iScore;
	float fSpeed;

	EGameState::EGameState CurrentGameState;

	int SetGameState(EGameState::EGameState GameState);
	EGameState::EGameState GetGameState();

	void AddScore();
	int GetScore();
	int RetsetScore();
};
