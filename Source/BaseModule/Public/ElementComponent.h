// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementComponent.generated.h"

UENUM(BlueprintType)
enum class EElementTypeEnum : uint8
{
	ET_Normal = 0 UMETA(DisplayName = "Normal"),
	ET_Flame = 1 UMETA(DisplayName = "Flame"),
	ET_Water = 2 UMETA(DisplayName = "Water"),
	ET_Air = 4 UMETA(DisplayName = "Air"),
	ET_FlameWater = ET_Flame + ET_Water UMETA(DisplayName = "FlameWater"),
	ET_FlameAir = ET_Flame + ET_Air UMETA(DisplayName = "FlameAir"),
	ET_WaterAir = ET_Water + ET_Air UMETA(DisplayName = "WaterAir"),
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

	void ChangeElementState(EElementTypeEnum p_ElementType);

	void ClearElementState();

	void PlayEffect(EElementTypeEnum p_State);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTypeEnum ElementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle clearTh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UElementDataAsset* elementDataAsset;
};
