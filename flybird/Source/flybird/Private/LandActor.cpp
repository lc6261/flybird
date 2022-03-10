// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

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
}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float sp = fSpeed * DeltaTime - 1;
	
	Land0->AddLocalOffset(FVector(sp, 0.0f, 0.0f));
	Land1->AddLocalOffset(FVector(sp, 0.0f, 0.0f));

	if(Land0->GetRelativeLocation().X <= -336.0f)
	{
		Land0->SetRelativeLocation(FVector(Land1->GetRelativeLocation().X + 336.0f, 0.0f, 0.0f));
	}

	if (Land1->GetRelativeLocation().X <= -336.0f)
	{
		Land1->SetRelativeLocation(FVector(Land0->GetRelativeLocation().X + 336.0f, 0.0f, 0.0f));
	}
	

}

