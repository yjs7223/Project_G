// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementDataTable.h"
#include "ElementComponent.generated.h"

UENUM(BlueprintType)
enum class EElementTypeEnum : uint8
{
	ET_Normal = 0 UMETA(DisplayName = "Normal"),
	ET_Venom = 1 UMETA(DisplayName = "Venom"),
	ET_Freeze = 2 UMETA(DisplayName = "Freeze"),
	ET_TongTong = 4 UMETA(DisplayName = "TongTong"),
	ET_Evaporation = ET_Venom + ET_Freeze UMETA(DisplayName = "Evaporation"),
	ET_Diffusion = ET_Venom + ET_TongTong UMETA(DisplayName = "Diffusion"),
	ET_Florescence = ET_Freeze + ET_TongTong UMETA(DisplayName = "Florescence"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASEMODULE_API UElementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeElementState(EElementTypeEnum p_ElementType, float p_Damage);

	void ClearElementState();

	void VenomAction(float p_Damage);

	void VenomTickDmg(float p_Damage);

	void FreezeAction();

	void TongTongAction(float p_Damage, int p_TongStack, FCollisionQueryParams p_Param);

	void TongTongStart(float p_Damage);

	void PlayEffect(EElementTypeEnum p_State);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTypeEnum ElementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int elementStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle clearTh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle VenomTickTh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UElementDataAsset* elementDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* elementDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FElementDataStruct elementData;
};
