// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYMODULE_API UEnemyDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* swordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimBlueprint* swordAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* swordWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* rifleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimBlueprint* rifleAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* rifleWeaponMesh;
};
