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
		USkeletalMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimBlueprint* anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* weaponMesh;
};
