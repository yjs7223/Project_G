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
	//데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;

	//연사속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fireRate;

	//장전된 탄약
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentAmmo;

	//남은 탄약
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int holdAmmo;

	//최대 장탄수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxAmmo;
};