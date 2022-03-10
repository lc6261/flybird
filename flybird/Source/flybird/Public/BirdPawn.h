// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPawn.generated.h"

UCLASS()
class FLYBIRD_API ABirdPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//¶¯»­
	UPROPERTY(VisibleAnywhere, Category = "UPaperFlipbookComponent|FlipbookComp")
	class UPaperFlipbookComponent* FlipComp;

	//Ðý±Û
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components|LCSpringArm")
	class USpringArmComponent* SpringArm;

	//ÉãÏñÍ·
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components|LcCamera")
	class UCameraComponent* Camera;
};
