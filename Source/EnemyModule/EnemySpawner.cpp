// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ST_Spawn.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerOn = false;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	curWave = 0;

	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	pointTime = 0;
	pointSpawnCheck = false;
	SetDataTable(curWave);
	//Total_EnemyNum = (spawn_Wave[Enemy_Name::ENEMY1] + spawn_Wave[Enemy_Name::ENEMY2]);
	/*TArray<AActor*> basechars;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), basechars);*/

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WaveControl(DeltaTime);
}

void AEnemySpawner::SpawnWave()
{
	AEnemy* enemy = nullptr;
	//������
	if (rifleCount < spawn_Wave[Enemy_Name::ENEMY1])
	{
		// ���� ��ġ �˻� �� ����
		spawn_Spot = SetSpawnSpot(spawn_Spot);

		// ����
		APawn* temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), CloseRangeEnemy, BT_Enemy, spawn_Spots[spawn_Spot]->GetActorLocation());

		enemy = Cast<AEnemy>(temp);

		// �����Ǹ鼭 �ڽ��� ������ �����ʸ� �����ϵ��� ��
		if (enemy != nullptr)
		{
			enemy->mySpawner = this;

			rifleCount++;
			if (enemy->GetController() != nullptr)
			{
				EnemyController = Cast<AEnemyController>(Cast<AEnemy>(enemy)->GetController());
				if (EnemyController != nullptr)
				{
					if (EnemyController->GetBlackboardComponent() != nullptr)
					{
						EnemyController->GetBlackboardComponent()->SetValueAsObject("SetTarget", player);
						//EnemyController->GetBlackboardComponent()->SetValueAsEnum("Combat", 1);
					}

				}
			}
		}
	}
	else if (sniperCount < spawn_Wave[Enemy_Name::ENEMY2])
	{
		// ���� ��ġ �˻� �� ����
		spawn_Spot = SetSpawnSpot(spawn_Spot);

		// ����
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Spawn!"));
		APawn* temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), LongRangeEnemy, BT_Enemy, spawn_Spots[spawn_Spot]->GetActorLocation());

		enemy = Cast<AEnemy>(temp);
		// �����Ǹ鼭 �ڽ��� ������ �����ʸ� �����ϵ��� ��
		if (enemy != nullptr)
		{
			enemy->mySpawner = this;

			sniperCount++;
			if (enemy->GetController() != nullptr)
			{
				EnemyController = Cast<AEnemyController>(Cast<AEnemy>(enemy)->GetController());
				if (EnemyController != nullptr)
				{
					EnemyController->GetBlackboardComponent()->SetValueAsObject("Target", player);
				}
			}
		}
	}
	else
	{
		// ���� �Ϸ�
		spawnCheck = true;
		rifleCount = 0;
		sniperCount = 0;
	}
}

void AEnemySpawner::WaveControl(const float DeltaTime)
{
	if (curSpawnData == nullptr || spawn_Spots.Num() <= 0)
	{
		return;
	}
	if (TriggerOn == true)
	{
		SetDataTable(curWave);
		if (!check_Overlap)
		{
			check_Overlap = true;
		}
		if (waveEnd)
		{
			waveEnd = false;
		}
		if (spawnCheck)
		{
			spawnCheck = false;
		}

	}
	// ������ ���̺����� Ȯ�� �� ����
	if (check_Overlap && !spawnCheck)
	{
		switch (spawn_Type)
		{
		case Spawn_Type::KILL:
			if (count_Kill >= spawn_Condition)
			{
				spawn_Delay += DeltaTime;
				if (spawn_Delay >= (*curSpawnData).spawn_Delay)
				{
					SpawnWave();
					spawn_Delay = 0;
				}
			}
			break;
		case Spawn_Type::SECONDS:
			spawn_Timer += DeltaTime;
			if (spawn_Timer >= spawn_Condition)
			{
				spawn_Delay += DeltaTime;
				if (spawn_Delay >= (*curSpawnData).spawn_Delay)
				{
					SpawnWave();
					spawn_Delay = 0;
					count_Kill = 0;
				}
			}
			break;
		case Spawn_Type::TRIGGER:
			if (TriggerOn)
			{
				spawn_Delay += DeltaTime;
				if (spawn_Delay >= (*curSpawnData).spawn_Delay)
				{
					SpawnWave();
					spawn_Delay = 0;
					count_Kill = 0;
				}
			}
		}
	}

	if (last_Spawn && spawnCheck)
	{
		TriggerOn = false;
		check_Overlap = false;
		waveEnd = true;
		curWave = 0;

	}
	// ���� ���̺�
	else if (spawnCheck)
	{
		NextWave();
	}
}

int AEnemySpawner::SetSpawnSpot(int p_Spawn_Pos)
{
	// �÷��̾�� ������ �ʴٸ� ��ȯ
	if (spawn_Spots[spawn_Spot]->GetDistanceTo(player) >= 0)
	{
		p_Spawn_Pos = spawn_Spot;
	}
	else
	{
		for (int i = 0; i < spawn_Spots.Num(); i++)
		{
			// �÷��̾� �Ÿ��� 50���� ū ������ġ��
			if (spawn_Spots[i]->GetDistanceTo(player) > 50)
			{
				// ó�� ���� �Ŷ�� �ϴ� �ֱ�
				if (p_Spawn_Pos == spawn_Spot)
				{
					p_Spawn_Pos = i;
				}
				// ���� �� ���� �� Ȯ���ϰ� ���� �ɷ� �ֱ�
				if (spawn_Spots[p_Spawn_Pos]->GetDistanceTo(player) >
					spawn_Spots[i]->GetDistanceTo(player))
				{
					p_Spawn_Pos = i;
				}
			}
		}
	}
	return p_Spawn_Pos;
}

void AEnemySpawner::NextWave()
{
	count_Kill = 0;
	spawn_Timer = 0;
	// ���� ���̺�� �ѱ��
	SetDataTable(++curWave);
	spawnCheck = false;
}

void AEnemySpawner::SpawnEnable(bool p_flag)
{
	check_Overlap = p_flag;
}

void AEnemySpawner::TriggerOnTrue()
{
	TriggerOn = true;
}

void AEnemySpawner::SetDataTable(int p_curWave)
{
	if (spawnData != nullptr)
	{
		curSpawnData = spawnData->FindRow<FST_Spawner>(*FString::FromInt(p_curWave), TEXT(""));
		if (curSpawnData != nullptr)
		{
			last_Spawn = curSpawnData->last_Spawn;
			spawn_Condition = curSpawnData->spawn_Condition;
			spawn_Delay = curSpawnData->spawn_Delay;
			spawn_Spot = curSpawnData->spawn_Spot;
			spawn_Type = curSpawnData->spawn_Type;
			spawn_Wave = curSpawnData->spawn_Wave;
		}
	}
}