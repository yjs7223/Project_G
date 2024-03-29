// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementComponent.h"
#include "ElementDataAsset.h"
#include "BaseStatComponent.h"

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
	//GetWorld()->GetTimerManager().ClearTimer(clearTh);
	
	switch (ElementState)
	{
	case EElementTypeEnum::ET_Normal:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);
		ElementState = p_ElementType;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, text);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 8.f, false);
		break;
	case EElementTypeEnum::ET_Flame:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Water)
		{
			ElementState = EElementTypeEnum::ET_FlameWater;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_FlameAir;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_Water:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_FlameWater;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_WaterAir;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_Air:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Water)
		{
			ElementState = EElementTypeEnum::ET_WaterAir;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_FlameAir;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_FlameWater:
		//GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_FlameAir:
		//GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_WaterAir:
		//GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	default:
		break;
	}

}

void UElementComponent::ClearElementState()
{
	ElementState = EElementTypeEnum::ET_Normal;
}

void UElementComponent::PlayEffect(EElementTypeEnum p_State)
{
	if (elementDataAsset)
	{
		UBaseStatComponent* stat = GetOwner()->FindComponentByClass<UBaseStatComponent>();
		if (stat)
		{
			switch (p_State)
			{
			case EElementTypeEnum::ET_Normal:
				break;
			case EElementTypeEnum::ET_Flame:
				break;
			case EElementTypeEnum::ET_Water:
				break;
			case EElementTypeEnum::ET_Air:
				break;
			case EElementTypeEnum::ET_FlameWater:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->smokeEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			case EElementTypeEnum::ET_FlameAir:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->explosionEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			case EElementTypeEnum::ET_WaterAir:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->sparkEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			default:
				break;
			}
		}
	
	}
}


