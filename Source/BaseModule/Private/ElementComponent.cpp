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
			ElementState = EElementTypeEnum::ET_Evaporation;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_Diffusion;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_Water:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_Evaporation;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Air)
		{
			ElementState = EElementTypeEnum::ET_Florescence;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_Air:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Water)
		{
			ElementState = EElementTypeEnum::ET_Florescence;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Flame)
		{
			ElementState = EElementTypeEnum::ET_Diffusion;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_Evaporation:
		//GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_Diffusion:
		//GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 5.f, false);
		break;
	case EElementTypeEnum::ET_Florescence:
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
			case EElementTypeEnum::ET_Evaporation:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->EvaporationEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			case EElementTypeEnum::ET_Diffusion:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->DiffusionEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			case EElementTypeEnum::ET_Florescence:
				GetWorld()->SpawnActor<AActor>(elementDataAsset->FlorescenceEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

				stat->Attacked(50.f);
				break;
			default:
				break;
			}
		}
	
	}
}


