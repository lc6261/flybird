// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "../flybirdGameModeBase.h"
#include "BirdGameStateBase.h"

// Sets default values
ALandActor::ALandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Land0 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Land0"));
	Land0->SetupAttachment(RootComponent);
	//导入背景资源
	static ConstructorHelpers::FObjectFinder<UPaperSprite> LandText0(TEXT("PaperSprite'/Game/flybird/textures/land_Sprite.land_Sprite'"));
	if (LandText0.Succeeded())
	{
		Land0->SetSprite(LandText0.Object);
	}



	Land1 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Land1"));
	Land1->SetupAttachment(RootComponent);
	//导入背景资源
	static ConstructorHelpers::FObjectFinder<UPaperSprite> LandText1(TEXT("PaperSprite'/Game/flybird/textures/land_Sprite.land_Sprite'"));
	if (LandText1.Succeeded())
	{
		Land1->SetSprite(LandText1.Object);
	}

	fSpeed = 60.0f;
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
	if (Land0)
	{
		Land0->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	if (Land1)
	{
		Land1->SetRelativeLocation(FVector(336.0f, 0.0f, 0.0f));
	}


	//获取当前世界游戏模式类
	GameModeBase = GetWorld()->GetAuthGameMode();
	//转换为当前游戏模式类
	CurrenteModeBase = Cast<AflybirdGameModeBase>(GameModeBase);
	if (GameModeBase)
	{
		//游戏模式获取游戏状态类
		BirdGameStateBase = CurrenteModeBase->GetGameState<ABirdGameStateBase>();
	}
}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LandRun(DeltaTime);
}
void ALandActor::LandRun(float DeltaTime)
{
	float sp = fSpeed * DeltaTime - 1;
	POINT_NULL_RETURN(BirdGameStateBase);

	if (BirdGameStateBase->GetGameState() != EGameState::EGAME_RUNING)
		return;

	Land0->AddLocalOffset(FVector(sp, 0.0f, 0.0f));
	Land1->AddLocalOffset(FVector(sp, 0.0f, 0.0f));

	if (Land0->GetRelativeLocation().X <= -336.0f)
	{
		Land0->SetRelativeLocation(FVector(Land1->GetRelativeLocation().X + 336.0f, 0.0f, 0.0f));
	}

	if (Land1->GetRelativeLocation().X <= -336.0f)
	{
		Land1->SetRelativeLocation(FVector(Land0->GetRelativeLocation().X + 336.0f, 0.0f, 0.0f));
	}

}
