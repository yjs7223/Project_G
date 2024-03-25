// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Weapon.h"
#include "ElementComponent.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE(FOnFireDelegate)
DECLARE_DELEGATE(FOnSwapWeaponDelegate)
DECLARE_DELEGATE(FOnSwapElementDelegate)
DECLARE_DELEGATE(FOnToggleWeaponOverlayDelegate)
DECLARE_DELEGATE(FOnToggleElementOverlayDelegate)
DECLARE_DELEGATE_OneParam(FOnChangeWeaponTypeDelegate, EWeaponTypeEnum)
DECLARE_DELEGATE_OneParam(FOnChangeElementTypeDelegate, EElementTypeEnum)

/**
 * 
 */
UCLASS()
class PLAYERMODULE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	FOnFireDelegate OnFireDelegate;
	FOnSwapWeaponDelegate OnSwapWeaponDelegate;
	FOnSwapElementDelegate OnSwapElementDelegate;
	FOnToggleWeaponOverlayDelegate OnToggleWeaponOverlayDelegate;
	FOnToggleElementOverlayDelegate OnToggleElementOverlayDelegate;
	FOnChangeWeaponTypeDelegate OnChangeWeaponTypeDelegate;
	FOnChangeElementTypeDelegate OnChangeElementTypeDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Moving();

	void MoveForward(float input);
	void MoveRight(float input);

	void Turn(float inputVec);
	void LookUp(float inputVec);

	void SetWeaponRotation();

	void StartFire();
	void StopFire();

	void StartSwapWeapon();
	void StopSwapWeapon();

	void StartSwapElement();
	void StopSwapElement();

	void CheckHoldingKey();

	void StartJump();
	void StopJump();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* weaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector inputVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator r;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPlayerWidget* PlayerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle fireTh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwapWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSwapElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float weaponHoldingtime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float elementHoldingtime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int jumpCount;
};
