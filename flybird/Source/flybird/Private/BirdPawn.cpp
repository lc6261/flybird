// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"

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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LCSpringArm"));
	//��������������
	SpringArm->SetupAttachment(FlipComp);

	SpringArm->SetRelativeRotation(FRotator( 0.0f, -90.0f, 0.0f));
	//SpringArm->TargetArmLength = 400.0f;

	//��ͷ�ӳ�,ƽ������
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	//�����������������
	Camera->SetupAttachment(SpringArm);
	//�������
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//��������Ŀ��
	Camera->OrthoWidth = 1000;
}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

