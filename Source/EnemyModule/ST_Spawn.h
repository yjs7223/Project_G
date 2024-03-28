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
	// ���� ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESpawnType spawnType;

	// ���� ���� ������ ������ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnDelay;

	// �� ���̺긶�� ��ȯ�� ���ֵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EEnemyName, int> spawn_Wave =
		{
			{EEnemyName::ENEMY1, 0}
			, {EEnemyName::ENEMY2, 0}
		};

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnCondition;

	// ������ ������ ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawnSpot;
	// �̷����ϸ� ���͸� ���� ���� ������ ������ �ȵ�
	//TWeakObjectPtr<AActor> spawn_Spot;

	// ������ ���̺����� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLastSpawn;
};