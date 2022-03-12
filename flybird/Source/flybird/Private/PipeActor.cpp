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
#define MAXSIZE 5 //循环队列的最大容量

typedef int DataType; //循环队列中元素类型

typedef struct Queue
{
	DataType queue[MAXSIZE];
	int front;
	int rear;
}SeqQueue;

//队列初始化, 将循环队列初始化为空队列
void InitQueue(SeqQueue* SQ)
{
	if (!SQ) return;

	SQ->front = 0;
	SQ->rear = 0;
};

//判断队列为空
int IsEmpty(SeqQueue* SQ)
{
	if (!SQ) return 0;

	if (SQ->front == SQ->rear)
	{
		return 1;
	}

	return 0;
}


//判断循环队列是否为满
int IsFull(SeqQueue* SQ)
{
	if (!SQ) return 0;

	if ((SQ->rear + 1) % MAXSIZE == SQ->front)
	{
		return 1;
	}

	return 0;
}

//入队, 将元素data插入到循环队列SQ中
int EnterQueue(SeqQueue* SQ, DataType data)
{
	if (!SQ) return 0;

	if (IsFull(SQ))
	{
		return 0;
	}

	SQ->queue[SQ->rear] = data; //在队尾插入元素data
	SQ->rear = (SQ->rear + 1) % MAXSIZE; //队尾指针循环后移一位

	return 1;
}

//出队, 将队列中队头的元素data出队, 出队后 队头指针 front 后移一位
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


//打印队列中的各个元素

void PrintQueue(SeqQueue* SQ)
{
	if (!SQ) return;
	int i = SQ->front;
	while (i != SQ->rear)
	{
		i = (i + 1) % MAXSIZE;
	}
}
//获取队首元素, 不出队
int GetHeand(SeqQueue * SQ, DataType * data)
{

	if (!SQ || IsEmpty(SQ))
	{
	}
	return *data = SQ->queue[SQ->front];
}

//获取队列中元素的个数
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
		//建立上+下管道组
		FString GrpName = FString::Printf(TEXT("Group:%d"), i);
		USceneComponent* SceneGrp = CreateDefaultSubobject<USceneComponent>(*GrpName);
		SceneGrp->SetupAttachment(RootComponent);
		PipeGroup.Add(SceneGrp);



		//建立上管道
		FString UpPipeName = FString::Printf(TEXT("UpPipe:%d"), i);
		UPaperSpriteComponent* UpPipeGrp = CreateDefaultSubobject<UPaperSpriteComponent>(*UpPipeName);
		UpPipeGrp->SetupAttachment(SceneGrp);
		if (UpText.Object)
		{
			UpPipeGrp->SetSprite(UpText.Object);
		}
		UpPipeGrp->SetupAttachment(SceneGrp);
		UpPipeGrp->SetRelativeLocation(FVector(0.0f, 0.0f, -210.0f));//设置相对于Grp的位置


		//建立下管道
		FString DownPipeName = FString::Printf(TEXT("DownPipe:%d"), i);
		UPaperSpriteComponent* DownPipeGrp = CreateDefaultSubobject<UPaperSpriteComponent>(*DownPipeName);
		DownPipeGrp->SetupAttachment(SceneGrp);
		if (DownText.Object)
		{
			DownPipeGrp->SetSprite(DownText.Object);
		}
		DownPipeGrp->SetupAttachment(SceneGrp);
		DownPipeGrp->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));//设置相对于Grp的位置
	}
	bPlaySound = true;
#ifdef _QUEEN_BIRD_
	SeqQueue* SQ = new SeqQueue;
	DataType data = -1;
	//初始化队列
	InitQueue(SQ);
	//入队
	for (int i = 0; i < 7; i++)
	{
		EnterQueue(SQ, i);
	}


	//出队
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
	DoubleLinkList<int> list(data, 4);//初始化
	list.PrintAll();
	cout << "线性表的长度为" << list.GetLength() << endl;//获取链表的长度
	list.Insert(62, 4);//增
	list.PrintAll();
	list.Delete(3);//删
	list.PrintAll();
	list.Change(35, 1);//改
	list.PrintAll();
	int data1 = list.Search1(3);
	int pos1 = list.Search2(35);
	cout << "链表中位置3处的数据为  " << data1 << "数据35在链表中的位置为  " << pos1;//查
	while (1);
#endif
}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	PipeInit();
	CoinSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/sounds/coin.coin'"));



	//获取当前世界游戏模式类
	GameModeBase = GetWorld()->GetAuthGameMode();
	//转换为当前游戏模式类
	CurrenteModeBase = Cast<AflybirdGameModeBase>(GameModeBase);
	if (GameModeBase)
	{
		//游戏模式获取游戏状态类
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
		PipeGroup[i]->AddLocalOffset(FVector(sp, 0.0f, 0.0f));//设置偏移量，移动

		if (PipeGroup[i]->GetRelativeLocation().X < -400.0f)//管道复位
		{
			int idx = i - 1;
			if (idx < 0)
			{
				idx = 2;
			}
			x = FMath::FRandRange(250.0f, 300.0f);//随机宽度，间距
			z = FMath::FRandRange(120.0f, -120.0f);//随机高度
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