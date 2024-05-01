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

	if (elementDataTable)
	{
		elementData = *(elementDataTable->FindRow<FElementDataStruct>(FName("Preset1"), FString("")));
	}

	// ...
	
}


// Called every frame
void UElementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}

void UElementComponent::ChangeElementState(EElementTypeEnum p_ElementType, float p_Damage)
{
	//GetWorld()->GetTimerManager().ClearTimer(clearTh);
	switch (ElementState)
	{
	case EElementTypeEnum::ET_Normal:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);
		if (p_ElementType == EElementTypeEnum::ET_Venom)
		{
			VenomAction(p_Damage);
		}
		else if (p_ElementType == EElementTypeEnum::ET_Freeze)
		{
			ElementState = p_ElementType;
			GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 8.f, false);
		}
		else if (p_ElementType == EElementTypeEnum::ET_TongTong)
		{
			TongTongStart(p_Damage);
		}
		break;
	case EElementTypeEnum::ET_Venom:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);
		if (p_ElementType == EElementTypeEnum::ET_Venom)
		{
			VenomAction(p_Damage);
		}
		else if (p_ElementType == EElementTypeEnum::ET_Freeze)
		{
			ElementState = EElementTypeEnum::ET_Evaporation;
			GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		}
		else if (p_ElementType == EElementTypeEnum::ET_TongTong)
		{
			ElementState = EElementTypeEnum::ET_Diffusion;
			GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		}
		PlayEffect(ElementState);
		break;
	case EElementTypeEnum::ET_Freeze:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_Venom)
		{
			ElementState = EElementTypeEnum::ET_Evaporation;
		}
		else if (p_ElementType == EElementTypeEnum::ET_TongTong)
		{
			ElementState = EElementTypeEnum::ET_Florescence;
		}
		PlayEffect(ElementState);
		GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, 4.f, false);
		break;
	case EElementTypeEnum::ET_TongTong:
		GetWorld()->GetTimerManager().ClearTimer(clearTh);

		if (p_ElementType == EElementTypeEnum::ET_TongTong)
		{
			TongTongStart(p_Damage);
		}
		else if (p_ElementType == EElementTypeEnum::ET_Freeze)
		{
			ElementState = EElementTypeEnum::ET_Florescence;
		}
		else if (p_ElementType == EElementTypeEnum::ET_Venom)
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
	elementStack = 0;
	GetWorld()->GetTimerManager().ClearTimer(clearTh);
}

void UElementComponent::VenomAction(float p_Damage)
{
	GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, elementData.VenomTimeDuration, false);
	ElementState = EElementTypeEnum::ET_Venom;
	elementStack++;
	if (elementStack >= elementData.VenomMaxStack)
	{
		elementStack = elementData.VenomMaxStack;
	}

	if (!GetWorld()->GetTimerManager().IsTimerActive(VenomTickTh))
	{
		FTimerDelegate venomtickDelegate = FTimerDelegate::CreateUObject(this, &UElementComponent::VenomTickDmg, p_Damage);
		GetWorld()->GetTimerManager().SetTimer(VenomTickTh, venomtickDelegate, elementData.VenomTickRate, true);
	}
}

void UElementComponent::VenomTickDmg(float p_Damage)
{
	if (ElementState == EElementTypeEnum::ET_Venom)
	{
		UBaseStatComponent* stat = GetOwner()->FindComponentByClass<UBaseStatComponent>();
		float finaldmg = p_Damage * elementData.VenomTickDamagePercentage * elementStack;

		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::SanitizeFloat(finaldmg));
		stat->Attacked(finaldmg);
		if (stat->bDie)
		{
			GetWorld()->GetTimerManager().ClearTimer(VenomTickTh);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(VenomTickTh);
	}
}

void UElementComponent::FreezeAction()
{
	//슬로우는 ai와 협업할 것
}

void UElementComponent::TongTongAction(float p_Damage, int p_TongStack, FCollisionQueryParams p_Param)
{
	//통통탄 시작 스택 추가해야함
	GetWorld()->GetTimerManager().SetTimer(clearTh, this, &UElementComponent::ClearElementState, elementData.TongTongTimeDuration, false);
	ElementState = EElementTypeEnum::ET_TongTong;
	elementStack++;
	if (elementStack >= elementData.TongTongMaxStack)
	{
		elementStack = elementData.TongTongMaxStack;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::FromInt(p_TongStack));
	if (p_TongStack <= 0)
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::FromInt(p_TongStack));
	int m_TongStack = --p_TongStack;

	FVector start = GetOwner()->GetActorLocation();
	FVector end;
	end = start;
	FCollisionQueryParams param = p_Param;
	FHitResult result;
	param.AddIgnoredActor(GetOwner());
	//DrawDebugSphere(GetWorld(), start, elementData.TongTongMaxRange, 12, FColor::Green, false, 1.0f);
	if (GetWorld()->SweepSingleByChannel(result, start, end, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(elementData.TongTongMaxRange), param))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, result.GetActor()->GetName());
		result.GetActor()->FindComponentByClass<UElementComponent>()->TongTongAction(p_Damage, m_TongStack, param);
		//DrawDebugSphere(GetWorld(), start, elementData.TongTongMaxRange, 12, FColor::Red, false, 3.0f);
		
	}

}

void UElementComponent::TongTongStart(float p_Damage)
{
	FCollisionQueryParams param(NAME_None, true);
	TongTongAction(p_Damage, elementStack, param);
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
			case EElementTypeEnum::ET_Venom:
				break;
			case EElementTypeEnum::ET_Freeze:
				break;
			case EElementTypeEnum::ET_TongTong:
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


