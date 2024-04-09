// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyAttackComponent.h"
#include "ST_AttackData.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYMODULE_API UST_AttackData : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FST_SkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_AtkType attackType;

	// ���� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* attackMontage;

	// ���� ���� ������ ���� �̸�(�ٰŸ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rightHand;

	// ���� ���� ���� ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool leftHand;

	// ���� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLoop;

	// ����ü(���Ÿ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> bullet;

	// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float delay;
};