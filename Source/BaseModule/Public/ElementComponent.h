// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementComponent.generated.h"

UENUM(BlueprintType)
enum class EElementTypeEnum : uint8
{
	ET_Normal UMETA(DisplayName = "Normal"),
	ET_Flame UMETA(DisplayName = "Flame"),
	ET_Water UMETA(DisplayName = "Water"),
	ET_Air UMETA(DisplayName = "Air"),
	ET_FlameWater UMETA(DisplayName = "FlameWater"),
	ET_FlameAir UMETA(DisplayName = "FlameAir"),
	ET_WaterAir UMETA(DisplayName = "WaterAir"),
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

public:
	EElementTypeEnum ElementState;

	FTimerHandle clearTh;
};
