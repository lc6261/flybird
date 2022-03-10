// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "flybirdGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FLYBIRD_API AflybirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AflybirdGameModeBase();
protected:
	virtual void BeginPlay() override;
};
