// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERMODULE_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* RFMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* GLMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SGMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet> RfBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet> GLBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet> SGBullet;
};
