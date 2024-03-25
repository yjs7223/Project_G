// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"


/**
 * 
 */
UCLASS()
class PLAYERMODULE_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void ToggleWeaponSwapOverlay();

	void ToggleElementSwapOverlay();

	void ToggleSlowBackImage();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(EWeaponTypeEnum p_WeaponType);

	UFUNCTION(BlueprintCallable)
	void ChangeElement(EElementTypeEnum p_ElementType);

	UFUNCTION(BlueprintCallable)
	void SetVisibilityWeapon(bool p_bEnabled);

	UFUNCTION(BlueprintCallable)
	void SetVisibilityElement(bool p_bEnabled);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UOverlay* WeaponSwapOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UOverlay* ElementSwapOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* SlowBackImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Weapon1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Weapon2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Weapon3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Element1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Element2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Element3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* Element4;

};
