// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponDataTable.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERMODULE_API UWeaponDataTable : public UDataTable
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerWeaponStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;

	//����ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fireRate;

	//������ ź��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentAmmo;

	//���� ź��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int holdAmmo;

	//�ִ� ��ź��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxAmmo;
};