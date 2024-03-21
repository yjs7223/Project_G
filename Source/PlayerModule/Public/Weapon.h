// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementComponent.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponTypeEnum : uint8
{
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_GrenadeLauncher UMETA(DisplayName = "GrenadeLauncher"),
	WT_Shotgun UMETA(DisplayName = "Shotgun"),
};

UCLASS()
class PLAYERMODULE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void SwapWeapon();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(EWeaponTypeEnum p_WeaponType);

	UFUNCTION(BlueprintCallable)
	void SwapElement();

	UFUNCTION(BlueprintCallable)
	void ChangeElement(EElementTypeEnum p_ElementType);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* weaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerCharacter* pc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypeEnum weaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* PlayerWeaponDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWeaponDataAsset* PlayerWeaponDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTypeEnum ammoElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;

};
