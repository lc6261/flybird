// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPawn.generated.h"

namespace EBirdState
{
	enum EBirdType
	{
		EBIRD_IDLE,
		EBIRD_FLY,
		EBIRD_DEAD
	};
}

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

public:
	class ABirdGameStateBase* BirdGameStateBase;
	class AGameModeBase* GameModeBase;
	class AflybirdGameModeBase* CurrenteModeBase;
private:
	//动画
	UPROPERTY(VisibleAnywhere, Category = "UPaperFlipbookComponent|FlipbookComp")
	class UPaperFlipbookComponent* FlipComp;

	//旋臂
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components|BirdSpringArm")
	class USpringArmComponent* BirdSpringArm;

	//摄像头
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components|BirdCamera")
	class UCameraComponent* BirdCamera;

	//音效
	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components|BirdSound")
	class USoundBase* FlySound;
	class USoundBase* DeadSound;
	class USoundBase* CrashSound;

	void BirdJump();
	void BirdFaceUpdate();
	void BirdStateChange(EBirdState::EBirdType eBirdState);

	EBirdState::EBirdType BirdStateCurrent;

	//碰撞回调函数,需要用UFUNCTION
	UFUNCTION()
	void OnComponentHitEvent(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);




};
