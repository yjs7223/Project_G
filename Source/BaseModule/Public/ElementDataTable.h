// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ElementDataTable.generated.h"

/**
 * 
 */
UCLASS()
class BASEMODULE_API UElementDataTable : public UDataTable
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FElementDataStruct: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Venom")
	float VenomTickDamagePercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Venom")
	int VenomMaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Venom")
	float VenomTimeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Venom")
	float VenomTickRate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freeze")
	float FreezeSlowPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freeze")
	int FreezeMaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Freeze")
	float FreezeTimeDuration;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TongTong")
	float TongTongMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TongTong")
	int TongTongMaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TongTong")
	float TongTongTimeDuration;
};