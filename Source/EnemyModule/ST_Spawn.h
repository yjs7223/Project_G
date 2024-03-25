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
enum class Spawn_Type : uint8
{
	KILL, SECONDS, TRIGGER
};

UENUM(BlueprintType)
enum class Enemy_Name : uint8
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
		Spawn_Type spawn_Type;

	// ���� ���� ������ ������ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Delay;

	// �� ���̺긶�� ��ȯ�� ���ֵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<Enemy_Name, int> spawn_Wave =
		{
			{Enemy_Name::ENEMY1, 0}
			, {Enemy_Name::ENEMY2, 0}
		};

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawn_Condition;

	// ������ ������ ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawn_Spot;
	// �̷����ϸ� ���͸� ���� ���� ������ ������ �ȵ�
	//TWeakObjectPtr<AActor> spawn_Spot;

// ������ ���̺����� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool last_Spawn;
};