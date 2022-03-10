// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandActor.generated.h"

UCLASS()
class FLYBIRD_API ALandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//¶¯»­
	UPROPERTY(VisibleAnywhere, Category = "ALandActor|Land0")
	class UPaperSpriteComponent* Land0;

	UPROPERTY(VisibleAnywhere, Category = "ALandActor|Land1")
	class UPaperSpriteComponent* Land1;

	float fSpeed;
};
