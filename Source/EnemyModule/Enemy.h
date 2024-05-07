// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyDataTable.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYMODULE_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEnemy();

	// DefaultSetting

	// 기본 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		UDataTable* defaultDT;
	// 현재 데이터 테이블
	struct FEnemyDataStruct* curDefaultDT;

	// Enemy 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		E_WeaponType enemyType;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AActor* target;

	// AI Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyMoveSetting")
		float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyMoveSetting")
		float curSpeed;	// 현재 속도
	float slow;	// 속도 감소량

	// 스포너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AEnemySpawner* mySpawner;

	class AEnemyController* controller;
	class UElementComponent* ec;
	class UEnemyAttackComponent* eac;

	float eTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AActiveZone* az;

	// 주무기 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		TArray<E_WeaponType> weaponArr;

	// 데이터 에셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyDataAsset* enemyDA;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyAttackComponent* enemyAttackComponent;*/

	class USkeletalMeshComponent* weaponMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HpUpdate();
	void MovementUpdate();
	void DieCheck();
	void ElementalEffect(float t);

	void SetDataTable();
	void SetWeaponMesh();
};