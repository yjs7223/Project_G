// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementComponent.h"

// Sets default values for this component's properties
UElementComponent::UElementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ElementState = EElementTypeEnum::ET_Normal;
	// ...
}


// Called when the game starts
void UElementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UElementComponent::ChangeElementState(EElementTypeEnum p_ElementType)
{
	GetWorld()->GetTimerManager().ClearTimer(clearTh);

	switch (ElementState)
	{
	case EElementTypeEnum::ET_Normal:
		ElementState = p_ElementType;
		break;
	case EElementTypeEnum::ET_Flame:
		if (ElementState == EElementTypeEnum::ET_Water)
		{
			ElementState = EElementTypeEnum::ET_FlameWater;
		}
		else if (ElementState == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_FlameAir;
		}

		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 8.f, false);
		break;
	case EElementTypeEnum::ET_Water:
		if (ElementState == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_FlameWater;
		}
		else if (ElementState == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_WaterAir;
		}

		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 8.f, false);
		break;
	case EElementTypeEnum::ET_Air:
		if (ElementState == EElementTypeEnum::ET_Water)
		{
			ElementState = EElementTypeEnum::ET_WaterAir;
		}
		else if (ElementState == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_FlameAir;
		}

		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 8.f, false);
		break;
	case EElementTypeEnum::ET_FlameWater:
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_FlameAir:
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_WaterAir:
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	default:
		break;
	}
}

void UElementComponent::ClearElementState()
{
	ElementState = EElementTypeEnum::ET_Normal;
}

