// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyDataTable.generated.h"

UCLASS()
class ENEMYMODULE_API UEnemyDataTable : public UDataTable
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	Default = 0	UMETA(DisplayName = "Default"),
	Sword	UMETA(DisplayName = "Sword"),
	DuelSword	UMETA(DisplayName = "DuelSword"),
	GreatSword	UMETA(DisplayName = "GreatSword"),
	Rifle	UMETA(DisplayName = "Rifle"),
	GrenadeLauncher	UMETA(DisplayName = "GrenadeLauncher"),
	SelfExplosion	UMETA(DisplayName = "SelfExplosion"),
	MAX			UMETA(Hidden)
};

USTRUCT(Atomic, BlueprintType)
struct FEnemyDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed;

	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hp;

	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackDamage;

	// ���� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<E_WeaponType> weaponArr;
};