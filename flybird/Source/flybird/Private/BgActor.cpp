// Fill out your copyright notice in the Description page of Project Settings.


#include "BgActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ABgActor::ABgActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//根组件创建
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgActor"));
	//FlipComp->SetupAttachment(RootComponent);
 	SetRootComponent(PaperSprite);

	//导入背景资源
	static ConstructorHelpers::FObjectFinder<UPaperSprite> BgText(TEXT("PaperSprite'/Game/flybird/textures/bg_day_Sprite.bg_day_Sprite'"));
	if (BgText.Succeeded())
	{
		PaperSprite->SetSprite(BgText.Object);
	}

}

// Called when the game starts or when spawned
void ABgActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABgActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

