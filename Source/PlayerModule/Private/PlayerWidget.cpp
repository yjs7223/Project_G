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

		SetVisibilityElement(false);
		SetVisibilityWeapon(false);
	}
}

void UPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UPlayerWidget::ToggleWeaponSwapOverlay()
{
	if (ElementSwapOverlay->GetRenderOpacity() == 1.f)
	{
		return;
	}

	ToggleSlowBackImage();
	if (WeaponSwapOverlay->GetRenderOpacity() == 1.f)
	{
		WeaponSwapOverlay->SetRenderOpacity(.0f);
		SetVisibilityWeapon(false);
	}
	else
	{
		WeaponSwapOverlay->SetRenderOpacity(1.f);
		SetVisibilityWeapon(true);
	}
}

void UPlayerWidget::ToggleElementSwapOverlay()
{
	if (WeaponSwapOverlay->GetRenderOpacity() == 1.f)
	{
		return;
	}

	ToggleSlowBackImage();
	if (ElementSwapOverlay->GetRenderOpacity() == 1.f)
	{
		ElementSwapOverlay->SetRenderOpacity(.0f);
		SetVisibilityElement(false);
	}
	else
	{
		ElementSwapOverlay->SetRenderOpacity(1.f);
		SetVisibilityElement(true);
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
		const ULocalPlayer* LocalPlayer = pc->GetLocalPlayer();
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FViewport* Viewport = LocalPlayer->ViewportClient->Viewport;
			if (Viewport)
			{
				FVector2D ViewportSize;
				LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
				const int32 X = static_cast<int32>(ViewportSize.X * 0.5f);
				const int32 Y = static_cast<int32>(ViewportSize.Y * 0.5f);

				Viewport->SetMouse(X, Y);
			}
		}

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
		pc->GetPawn<APlayerCharacter>()->OnChangeWeaponTypeDelegate.ExecuteIfBound(p_WeaponType);
		
	}
}

void UPlayerWidget::ChangeElement(EElementTypeEnum p_ElementType)
{
	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		pc->GetPawn<APlayerCharacter>()->OnChangeElementTypeDelegate.ExecuteIfBound(p_ElementType);
		
	}
}

void UPlayerWidget::SetVisibilityWeapon(bool p_bEnabled)
{
	if (p_bEnabled)
	{
		Weapon1->SetVisibility(ESlateVisibility::Visible);
		Weapon2->SetVisibility(ESlateVisibility::Visible);
		Weapon3->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Weapon1->SetVisibility(ESlateVisibility::Hidden);
		Weapon2->SetVisibility(ESlateVisibility::Hidden);
		Weapon3->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerWidget::SetVisibilityElement(bool p_bEnabled)
{
	if (p_bEnabled)
	{
		Element1->SetVisibility(ESlateVisibility::Visible);
		Element2->SetVisibility(ESlateVisibility::Visible);
		Element3->SetVisibility(ESlateVisibility::Visible);
		Element4->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Element1->SetVisibility(ESlateVisibility::Hidden);
		Element2->SetVisibility(ESlateVisibility::Hidden);
		Element3->SetVisibility(ESlateVisibility::Hidden);
		Element4->SetVisibility(ESlateVisibility::Hidden);
	}
}
