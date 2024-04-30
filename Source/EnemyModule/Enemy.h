// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AActor* target;

	// AI Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyMoveSetting")
		float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyMoveSetting")
		float curSpeed;	// 현재 속도
	float slow;	// 속도 감소량


	// 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimMontage* jump_Montage;

	// 스포너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AEnemySpawner* mySpawner;

	class AEnemyController* controller;
	class UElementComponent* ec;
	class UEnemyAttackComponent* eac;

	float eTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyDefaultSetting")
		class AActiveZone* az;

	// 다음 콤보 실행 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCombo;
	// 다음 콤보 실행 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float comboDelay;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEnemyAttackComponent* enemyAttackComponent;*/

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
};