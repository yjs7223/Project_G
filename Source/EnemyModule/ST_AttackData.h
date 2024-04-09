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
	// 공격 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_AtkType attackType;

	// 공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* attackMontage;

	// 공격 범위 시작점 소켓 이름(근거리용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool rightHand;

	// 공격 범위 끝점 소켓 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool leftHand;

	// 루프 체크
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLoop;

	// 투사체(원거리용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> bullet;

	// 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float delay;
};