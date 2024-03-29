// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BASEMODULE_API UElementDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> sparkEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> explosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> smokeEffect;
};
