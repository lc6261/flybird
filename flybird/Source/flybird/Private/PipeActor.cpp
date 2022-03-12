// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Sound/SoundBase.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

#include "../doublelinklist.h"
#include "../flybirdGameModeBase.h"
#include "BirdGameStateBase.h"
//#define _QUEEN_BIRD_
#ifdef _QUEEN_BIRD_
#define MAXSIZE 5 //ѭ�����е��������

typedef int DataType; //ѭ��������Ԫ������

typedef struct Queue
{
	DataType queue[MAXSIZE];
	int front;
	int rear;
}SeqQueue;

//���г�ʼ��, ��ѭ�����г�ʼ��Ϊ�ն���
void InitQueue(SeqQueue* SQ)
{
	if (!SQ) return;

	SQ->front = 0;
	SQ->rear = 0;
};

//�ж϶���Ϊ��
int IsEmpty(SeqQueue* SQ)
{
	if (!SQ) return 0;

	if (SQ->front == SQ->rear)
	{
		return 1;
	}

	return 0;
}


//�ж�ѭ�������Ƿ�Ϊ��
int IsFull(SeqQueue* SQ)
{
	if (!SQ) return 0;

	if ((SQ->rear + 1) % MAXSIZE == SQ->front)
	{
		return 1;
	}

	return 0;
}

//���, ��Ԫ��data���뵽ѭ������SQ��
int EnterQueue(SeqQueue* SQ, DataType data)
{
	if (!SQ) return 0;

	if (IsFull(SQ))
	{
		return 0;
	}

	SQ->queue[SQ->rear] = data; //�ڶ�β����Ԫ��data
	SQ->rear = (SQ->rear + 1) % MAXSIZE; //��βָ��ѭ������һλ

	return 1;
}

//����, �������ж�ͷ��Ԫ��data����, ���Ӻ� ��ͷָ�� front ����һλ
int DeleteQueeue(SeqQueue* SQ, DataType* data)
{

	if (!SQ || IsEmpty(SQ))
	{
		return 0;
	}

	*data = SQ->queue[SQ->front];
	SQ->front = (SQ->front + 1) % MAXSIZE;

	return 1;
}


//��ӡ�����еĸ���Ԫ��

void PrintQueue(SeqQueue* SQ)
{
	if (!SQ) return;
	int i = SQ->front;
	while (i != SQ->rear)
	{
		i = (i + 1) % MAXSIZE;
	}
}
//��ȡ����Ԫ��, ������
int GetHeand(SeqQueue * SQ, DataType * data)
{

	if (!SQ || IsEmpty(SQ))
	{
	}
	return *data = SQ->queue[SQ->front];
}

//��ȡ������Ԫ�صĸ���
int getLength(SeqQueue* SQ)
{
	if (!SQ) return 0;

	return ((SQ->rear) - SQ->front + MAXSIZE) % MAXSIZE;
}
#endif
// Sets default values
APipeActor::APipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> DownText(TEXT("PaperSprite'/Game/flybird/textures/pipe_down_Sprite.pipe_down_Sprite'"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> UpText(TEXT("PaperSprite'/Game/flybird/textures/pipe_up_Sprite.pipe_up_Sprite'"));

	iPipeNum = 3;

	for (int i=0;i< iPipeNum;i++)
	{
		//������+�¹ܵ���
		FString GrpName = FString::Printf(TEXT("Group:%d"), i);
		USceneComponent* SceneGrp = CreateDefaultSubobject<USceneComponent>(*GrpName);
		SceneGrp->SetupAttachment(RootComponent);
		PipeGroup.Add(SceneGrp);



		//�����Ϲܵ�
		FString UpPipeName = FString::Printf(TEXT("UpPipe:%d"), i);
		UPaperSpriteComponent* UpPipeGrp = CreateDefaultSubobject<UPaperSpriteComponent>(*UpPipeName);
		UpPipeGrp->SetupAttachment(SceneGrp);
		if (UpText.Object)
		{
			UpPipeGrp->SetSprite(UpText.Object);
		}
		UpPipeGrp->SetupAttachment(SceneGrp);
		UpPipeGrp->SetRelativeLocation(FVector(0.0f, 0.0f, -210.0f));//���������Grp��λ��


		//�����¹ܵ�
		FString DownPipeName = FString::Printf(TEXT("DownPipe:%d"), i);
		UPaperSpriteComponent* DownPipeGrp = CreateDefaultSubobject<UPaperSpriteComponent>(*DownPipeName);
		DownPipeGrp->SetupAttachment(SceneGrp);
		if (DownText.Object)
		{
			DownPipeGrp->SetSprite(DownText.Object);
		}
		DownPipeGrp->SetupAttachment(SceneGrp);
		DownPipeGrp->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));//���������Grp��λ��
	}
	bPlaySound = true;
#ifdef _QUEEN_BIRD_
	SeqQueue* SQ = new SeqQueue;
	DataType data = -1;
	//��ʼ������
	InitQueue(SQ);
	//���
	for (int i = 0; i < 7; i++)
	{
		EnterQueue(SQ, i);
	}


	//����
	for (int i = 0; i < 4; i++)
	{
		if (DeleteQueeue(SQ, &data))
		{
		}
		else
		{
		}
	}
#endif
#if 0
	int data[4] = { 2, 3, 4, 12 };
	DoubleLinkList<int> list(data, 4);//��ʼ��
	list.PrintAll();
	cout << "���Ա�ĳ���Ϊ" << list.GetLength() << endl;//��ȡ����ĳ���
	list.Insert(62, 4);//��
	list.PrintAll();
	list.Delete(3);//ɾ
	list.PrintAll();
	list.Change(35, 1);//��
	list.PrintAll();
	int data1 = list.Search1(3);
	int pos1 = list.Search2(35);
	cout << "������λ��3��������Ϊ  " << data1 << "����35�������е�λ��Ϊ  " << pos1;//��
	while (1);
#endif
}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	PipeInit();
	CoinSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/coin.coin'"));



	//��ȡ��ǰ������Ϸģʽ��
	GameModeBase = GetWorld()->GetAuthGameMode();
	//ת��Ϊ��ǰ��Ϸģʽ��
	CurrenteModeBase = Cast<AflybirdGameModeBase>(GameModeBase);
	if (GameModeBase)
	{
		//��Ϸģʽ��ȡ��Ϸ״̬��
		BirdGameStateBase = CurrenteModeBase->GetGameState<ABirdGameStateBase>();
		if (BirdGameStateBase)
		{
			fSpeed = BirdGameStateBase->fSpeed;
		}
	}
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PipeMove(DeltaTime);
}

void APipeActor::PipeMove(float DeltaTime)
{
	float x = 0;
	float z = 0;
	float sp = 0;
	POINT_NULL_RETURN(BirdGameStateBase);

	if (BirdGameStateBase->GetGameState() != EGameState::EGAME_RUNING)
		return;

	sp = fSpeed * DeltaTime - 1;

	for (int i = 0; i < iPipeNum; i++)
	{
		PipeGroup[i]->AddLocalOffset(FVector(sp, 0.0f, 0.0f));//����ƫ�������ƶ�

		if (PipeGroup[i]->GetRelativeLocation().X < -400.0f)//�ܵ���λ
		{
			int idx = i - 1;
			if (idx < 0)
			{
				idx = 2;
			}
			x = FMath::FRandRange(250.0f, 300.0f);//�����ȣ����
			z = FMath::FRandRange(120.0f, -120.0f);//����߶�
			PipeGroup[i]->SetRelativeLocation(
				FVector(PipeGroup[idx]->GetRelativeLocation().X + x,
					0.0f,
					z));
			bPlaySound = true;
		}
		if (bPlaySound == true)
		{
			if (PipeGroup[i]->GetRelativeLocation().X < -200.0f)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), CoinSound);
				bPlaySound = false;

				if (BirdGameStateBase)
				{
					BirdGameStateBase->AddScore();
				}
			}
		}

	}
}

void APipeActor::PipeInit()
{
	float x = 0;
	float z = 0;

	for (int i = 0; i < iPipeNum; i++)
	{
		x += FMath::FRandRange(250.0f, 300.0f);
		z = FMath::FRandRange(120.0f, -120.0f);
		PipeGroup[i]->SetRelativeLocation(FVector(x, 0.0f, z));
	}
}