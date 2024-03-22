// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "PlayerCharacter.h"
#include "UMG.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerCharacter* pc = GetOwningPlayerPawn<APlayerCharacter>();
	if (pc)
	{
		pc->OnToggleElementOverlayDelegate.BindUObject(this, &UPlayerWidget::ToggleElementSwapOverlay);
		pc->OnToggleWeaponOverlayDelegate.BindUObject(this, &UPlayerWidget::ToggleWeaponSwapOverlay);
	}
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UPlayerWidget::ToggleWeaponSwapOverlay()
{
	ToggleSlowBackImage();
	if (WeaponSwapOverlay->GetRenderOpacity() == 1.f)
	{
		WeaponSwapOverlay->SetRenderOpacity(.0f);
	}
	else
	{
		WeaponSwapOverlay->SetRenderOpacity(1.f);
	}
}

void UPlayerWidget::ToggleElementSwapOverlay()
{
	ToggleSlowBackImage();
	if (ElementSwapOverlay->GetRenderOpacity() == 1.f)
	{
		ElementSwapOverlay->SetRenderOpacity(.0f);
	}
	else
	{
		ElementSwapOverlay->SetRenderOpacity(1.f);
	}
}

void UPlayerWidget::ToggleSlowBackImage()
{
	if (SlowBackImage->GetRenderOpacity() == 1.f)
	{
		SlowBackImage->SetRenderOpacity(.0f);
	}
	else
	{
		SlowBackImage->SetRenderOpacity(1.f);
	}

	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		if (!pc->bShowMouseCursor)
		{
			pc->SetInputMode(FInputModeGameAndUI());
			pc->bShowMouseCursor = true;
			pc->bEnableClickEvents = true;
			pc->bEnableMouseOverEvents = true;
		}
		else
		{
			pc->SetInputMode(FInputModeGameOnly());
			pc->bShowMouseCursor = false;
			pc->bEnableClickEvents = false;
			pc->bEnableMouseOverEvents = false;
		}
	}
}

void UPlayerWidget::ChangeWeapon(EWeaponTypeEnum p_WeaponType)
{
	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		/*pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;
		pc->bEnableClickEvents = false;
		pc->bEnableMouseOverEvents = false;*/
		pc->GetPawn<APlayerCharacter>()->OnChangeWeaponTypeDelegate.ExecuteIfBound(p_WeaponType);
		//GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);
	}
}

void UPlayerWidget::ChangeElement(EElementTypeEnum p_ElementType)
{
	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		/*pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;
		pc->bEnableClickEvents = false;
		pc->bEnableMouseOverEvents = false;*/
		pc->GetPawn<APlayerCharacter>()->OnChangeElementTypeDelegate.ExecuteIfBound(p_ElementType);
		//GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);
	}
}
