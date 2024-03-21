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


	// ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimMontage* jump_Montage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MovementSetting();
	void DieCheck();
};
