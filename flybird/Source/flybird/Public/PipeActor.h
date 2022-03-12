// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"

UCLASS()
class FLYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	class ABirdGameStateBase* BirdGameStateBase;
	class AGameModeBase* GameModeBase;
	class AflybirdGameModeBase* CurrenteModeBase;

private:

	TArray<class USceneComponent*> PipeGroup;

	void PipeMove(float DeltaTime);
	void PipeInit();
	int iPipeNum;
	float fSpeed;

	class USoundBase* CoinSound;


	bool bPlaySound;
//	int iScore;
};
