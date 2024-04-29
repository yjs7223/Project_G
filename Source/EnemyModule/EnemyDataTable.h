// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyDataTable.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYMODULE_API UEnemyDataTable : public UDataTable
{
	GENERATED_BODY()
};

USTRUCT(Atomic, BlueprintType)
struct FEnemyDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// �̵��ӵ�
	float moveSpeed;

	// ü��
	float hp;

	// ���ݷ�
	float attackDamage;
};