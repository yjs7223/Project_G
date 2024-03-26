// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ST_Spawn.generated.h"

/**
 * 
 */
class ENEMYMODULE_API ST_Spawn
{
public:
	ST_Spawn();
	~ST_Spawn();
};

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	KILL, SECONDS, TRIGGER
};

UENUM(BlueprintType)
enum class EEnemyName : uint8
{
	ENEMY1, ENEMY2
};

USTRUCT(Atomic, BlueprintType)
struct FST_Spawner : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// 생성 조건 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESpawnType spawnType;

	// 스폰 액터 사이의 딜레이 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnDelay;

	// 각 웨이브마다 소환할 유닛들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EEnemyName, int> spawn_Wave =
		{
			{EEnemyName::ENEMY1, 0}
			, {EEnemyName::ENEMY2, 0}
		};

	// 스폰 조건
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnCondition;

	// 유닛이 생성될 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawnSpot;
	// 이렇게하면 액터를 넣을 수는 있지만 저장이 안됨
	//TWeakObjectPtr<AActor> spawn_Spot;

	// 마지막 웨이브인지 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLastSpawn;
};