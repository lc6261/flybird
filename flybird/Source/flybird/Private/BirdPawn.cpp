// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "Sound/SoundBase.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "../flybirdGameModeBase.h"
#include "BirdGameStateBase.h"
// Sets default values
ABirdPawn::ABirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//根组件创建
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	FlipComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipComp"));
	FlipComp->SetupAttachment(RootComponent);
	//导入资源
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PaperFlipbook(TEXT("PaperFlipbook'/Game/flybird/flipbooks/redbird.redbird'"));
	if (PaperFlipbook.Succeeded())
	{
		FlipComp->SetFlipbook(PaperFlipbook.Object);
	}

	//创建旋臂
	BirdSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BirdSpringArm"));
	//依附到FlipComp上
	BirdSpringArm->SetupAttachment(RootComponent);

	BirdSpringArm->SetRelativeRotation(FRotator( 0.0f, -90.0f, 0.0f));
	//SpringArm->TargetArmLength = 400.0f;

	//镜头延迟,平滑跟随
	//BirdSpringArm->bEnableCameraLag = true;
	//BirdSpringArm->CameraLagSpeed = 3.0f;

	BirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	//摄像机依附到悬臂上
	BirdCamera->SetupAttachment(BirdSpringArm);
	//正交相机
	BirdCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//正交相机的宽度
	BirdCamera->OrthoWidth = 1000;
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();

	CrashSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/crash.crash'"));
	DeadSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/dead.dead'"));
	FlySound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/fly.fly'"));

	//设置碰撞属性
	FlipComp->GetBodyInstance()->bNotifyRigidBodyCollision = true;//碰撞回调激活,有调用顺序
	FlipComp->SetCollisionObjectType(ECC_Pawn);//设置碰撞对象类型，与pawn类型碰撞发生事件
	FlipComp->OnComponentHit.AddDynamic(this,&ABirdPawn::OnComponentHitEvent);//绑定回调函数

	FBodyInstance *pBody = FlipComp->GetBodyInstance();
	if (pBody)
	{
		pBody->bLockXRotation = true;
		pBody->bLockYRotation = true;
		pBody->bLockZRotation = true;

		pBody->bLockXTranslation = true;
		pBody->bLockYTranslation = true;
		pBody->CreateDOFLock();//配置锁定
	}
	BirdStateCurrent = EBirdState::EBIRD_IDLE;

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
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BirdFaceUpdate();
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定按钮和函数:按钮，按下，本组件，调用函数
	PlayerInputComponent->BindAction(TEXT("MouseLeft"), IE_Pressed, this,& ABirdPawn::BirdJump);
}

void ABirdPawn::BirdJump()
{
	POINT_NULL_RETURN(BirdGameStateBase);

	if (BirdStateCurrent == EBirdState::EBIRD_IDLE)
	{
		BirdStateChange(EBirdState::EBIRD_FLY);
		//打印到视口
		FString DebugMessage = FString::Printf(TEXT("BirdJump"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage); //3.0f 

		BirdGameStateBase->SetGameState(EGameState::EGAME_RUNING);
	}
	else
	{
		FString DebugMessage = FString::Printf(TEXT("BirdState:%d"), BirdStateCurrent);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage); //3.0f 
	}

	if (BirdStateCurrent == EBirdState::EBIRD_FLY)
	{
		if (GEngine)
		{	//打印到视口
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "jump"); //3.0f 
			UE_LOG(LogTemp, Warning, TEXT("jump"));
		}
		if (FlipComp)
		{
			//加速度清0
			FlipComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
			//添加Z轴的力，向上
			FlipComp->AddImpulse(FVector(0.0f, 0.0f, 1500.0f));
		}
		UGameplayStatics::PlaySound2D(GetWorld(), FlySound);
	}
}

void ABirdPawn::BirdFaceUpdate()
{
	if (BirdStateCurrent != EBirdState::EBIRD_FLY)
	{
		return;
	}
	FVector flyVector = FlipComp->GetPhysicsLinearVelocity();
	FlipComp->SetRelativeRotation(FRotator(flyVector.Z*0.1f,0,0));;
}

void ABirdPawn::BirdStateChange(EBirdState::EBirdType eBirdState)
{
	if (FlipComp)
	{
		switch (eBirdState)
		{
			case EBirdState::EBIRD_IDLE:
				FlipComp->SetSimulatePhysics(false);
				break;
			case EBirdState::EBIRD_FLY:
				FlipComp->SetSimulatePhysics(true);
				break;
			case EBirdState::EBIRD_DEAD:
				//设置碰撞属性
				//FlipComp->GetBodyInstance()->bNotifyRigidBodyCollision = false;//碰撞回调激活
				FlipComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);//忽略所有通道
				break;
		}
	}
	BirdStateCurrent = eBirdState;
}

void ABirdPawn::OnComponentHitEvent(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	POINT_NULL_RETURN(BirdGameStateBase);
	BirdStateChange(EBirdState::EBIRD_DEAD);
	BirdGameStateBase->SetGameState(EGameState::EGAME_OVER);
	UGameplayStatics::PlaySound2D(GetWorld(), CrashSound);
	UGameplayStatics::PlaySound2D(GetWorld(), DeadSound);
}

