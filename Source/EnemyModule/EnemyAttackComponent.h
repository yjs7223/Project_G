// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"


UENUM(BlueprintType)
enum class E_AtkType : uint8
{
	None = 0	UMETA(Hidden),
	Enemy1	UMETA(DisplayName = "Enemy1"),
	Enemy2	UMETA(DisplayName = "Enemy2"),
	MAX			UMETA(Hidden)
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENEMYMODULE_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyAttackComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		E_AtkType AtkType;

	// stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		float attackDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		float attackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		float attackDamage;

	// ¸ùÅ¸ÁÖ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimMontage* attack_Montage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FHitResult m_result;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void CloseRangeAttack();
	UFUNCTION(BlueprintCallable)
		void LongRangeAttack();
		

};