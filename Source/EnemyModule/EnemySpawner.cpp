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
	bTriggerOn = false;
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
	//라이플
	if (rifleCount < spawnWave[EEnemyName::ENEMY1])
	{
		// 스폰 위치 검사 후 변경
		spawnSpot = SetSpawnSpot(spawnSpot);

		// 생성
		APawn* temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), CloseRangeEnemy, BT_Enemy, spawn_Spots[spawnSpot]->GetActorLocation());

		enemy = Cast<AEnemy>(temp);

		// 생성되면서 자신을 생성한 스포너를 저장하도록 함
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
	else if (sniperCount < spawnWave[EEnemyName::ENEMY2])
	{
		// 스폰 위치 검사 후 변경
		spawnSpot = SetSpawnSpot(spawnSpot);

		// 생성
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Spawn!"));
		APawn* temp = UAIBlueprintHelperLibrary::SpawnAIFromClass(GetWorld(), LongRangeEnemy, BT_Enemy, spawn_Spots[spawnSpot]->GetActorLocation());

		enemy = Cast<AEnemy>(temp);
		// 생성되면서 자신을 생성한 스포너를 저장하도록 함
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
		// 스폰 완료
		bSpawnCheck = true;
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
	if (bTriggerOn == true)
	{
		SetDataTable(curWave);
		if (!bCheckEnable)
		{
			bCheckEnable = true;
		}
		if (waveEnd)
		{
			waveEnd = false;
		}
		if (bSpawnCheck)
		{
			bSpawnCheck = false;
		}

	}
	// 마지막 웨이브인지 확인 및 스폰
	if (bCheckEnable && !bSpawnCheck)
	{
		switch (spawnType)
		{
		case ESpawnType::KILL:
			if (countKill >= spawnCondition)
			{
				spawnDelay += DeltaTime;
				if (spawnDelay >= (*curSpawnData).spawnDelay)
				{
					SpawnWave();
					spawnDelay = 0;
				}
			}
			break;
		case ESpawnType::SECONDS:
			spawnTimer += DeltaTime;
			if (spawnTimer >= spawnCondition)
			{
				spawnDelay += DeltaTime;
				if (spawnDelay >= (*curSpawnData).spawnDelay)
				{
					SpawnWave();
					spawnDelay = 0;
					countKill = 0;
				}
			}
			break;
		case ESpawnType::TRIGGER:
			if (bTriggerOn)
			{
				spawnDelay += DeltaTime;
				if (spawnDelay >= (*curSpawnData).spawnDelay)
				{
					SpawnWave();
					spawnDelay = 0;
					countKill = 0;
				}
			}
		}
	}

	if (lastSpawn && bSpawnCheck)
	{
		bTriggerOn = false;
		bCheckEnable = false;
		waveEnd = true;
		curWave = 0;

	}
	// 다음 웨이브
	else if (bSpawnCheck)
	{
		NextWave();
	}
}

int AEnemySpawner::SetSpawnSpot(int p_Spawn_Pos)
{
	// 플레이어와 가깝지 않다면 소환
	if (spawn_Spots[spawnSpot]->GetDistanceTo(player) >= 0)
	{
		p_Spawn_Pos = spawnSpot;
	}
	else
	{
		for (int i = 0; i < spawn_Spots.Num(); i++)
		{
			// 플레이어 거리가 50보다 큰 스폰위치가
			if (spawn_Spots[i]->GetDistanceTo(player) > 50)
			{
				// 처음 들어온 거라면 일단 넣기
				if (p_Spawn_Pos == spawnSpot)
				{
					p_Spawn_Pos = i;
				}
				// 누가 더 작은 지 확인하고 작은 걸로 넣기
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
	countKill = 0;
	spawnTimer = 0;
	// 다음 웨이브로 넘기기
	SetDataTable(++curWave);
	bSpawnCheck = false;
}

void AEnemySpawner::SpawnEnable(bool p_flag)
{
	bCheckEnable = p_flag;
}

void AEnemySpawner::TriggerOnTrue()
{
	bTriggerOn = true;
}

void AEnemySpawner::SetDataTable(int p_curWave)
{
	if (spawnData != nullptr)
	{
		curSpawnData = spawnData->FindRow<FST_Spawner>(*FString::FromInt(p_curWave), TEXT(""));
		if (curSpawnData != nullptr)
		{
			lastSpawn = curSpawnData->bLastSpawn;
			spawnCondition = curSpawnData->spawnCondition;
			spawnDelay = curSpawnData->spawnDelay;
			spawnSpot = curSpawnData->spawnSpot;
			spawnType = curSpawnData->spawnType;
			spawnWave = curSpawnData->spawn_Wave;
		}
	}
}