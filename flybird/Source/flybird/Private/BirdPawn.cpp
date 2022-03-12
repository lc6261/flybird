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
	//���������
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	FlipComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipComp"));
	FlipComp->SetupAttachment(RootComponent);
	//������Դ
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> PaperFlipbook(TEXT("PaperFlipbook'/Game/flybird/flipbooks/redbird.redbird'"));
	if (PaperFlipbook.Succeeded())
	{
		FlipComp->SetFlipbook(PaperFlipbook.Object);
	}

	//��������
	BirdSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BirdSpringArm"));
	//������FlipComp��
	BirdSpringArm->SetupAttachment(RootComponent);

	BirdSpringArm->SetRelativeRotation(FRotator( 0.0f, -90.0f, 0.0f));
	//SpringArm->TargetArmLength = 400.0f;

	//��ͷ�ӳ�,ƽ������
	//BirdSpringArm->bEnableCameraLag = true;
	//BirdSpringArm->CameraLagSpeed = 3.0f;

	BirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	//�����������������
	BirdCamera->SetupAttachment(BirdSpringArm);
	//�������
	BirdCamera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//��������Ŀ��
	BirdCamera->OrthoWidth = 1000;
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();

	CrashSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/crash.crash'"));
	DeadSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/dead.dead'"));
	FlySound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/fly.fly'"));

	//������ײ����
	FlipComp->GetBodyInstance()->bNotifyRigidBodyCollision = true;//��ײ�ص�����,�е���˳��
	FlipComp->SetCollisionObjectType(ECC_Pawn);//������ײ�������ͣ���pawn������ײ�����¼�
	FlipComp->OnComponentHit.AddDynamic(this,&ABirdPawn::OnComponentHitEvent);//�󶨻ص�����

	FBodyInstance *pBody = FlipComp->GetBodyInstance();
	if (pBody)
	{
		pBody->bLockXRotation = true;
		pBody->bLockYRotation = true;
		pBody->bLockZRotation = true;

		pBody->bLockXTranslation = true;
		pBody->bLockYTranslation = true;
		pBody->CreateDOFLock();//��������
	}
	BirdStateCurrent = EBirdState::EBIRD_IDLE;

	//��ȡ��ǰ������Ϸģʽ��
	GameModeBase = GetWorld()->GetAuthGameMode();
	//ת��Ϊ��ǰ��Ϸģʽ��
	CurrenteModeBase = Cast<AflybirdGameModeBase>(GameModeBase);
	if (GameModeBase)
	{
		//��Ϸģʽ��ȡ��Ϸ״̬��
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
	//�󶨰�ť�ͺ���:��ť�����£�����������ú���
	PlayerInputComponent->BindAction(TEXT("MouseLeft"), IE_Pressed, this,& ABirdPawn::BirdJump);
}

void ABirdPawn::BirdJump()
{
	POINT_NULL_RETURN(BirdGameStateBase);

	if (BirdStateCurrent == EBirdState::EBIRD_IDLE)
	{
		BirdStateChange(EBirdState::EBIRD_FLY);
		//��ӡ���ӿ�
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
		{	//��ӡ���ӿ�
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "jump"); //3.0f 
			UE_LOG(LogTemp, Warning, TEXT("jump"));
		}
		if (FlipComp)
		{
			//���ٶ���0
			FlipComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
			//���Z�����������
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
				//������ײ����
				//FlipComp->GetBodyInstance()->bNotifyRigidBodyCollision = false;//��ײ�ص�����
				FlipComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);//��������ͨ��
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

