// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"


UENUM(BlueprintType)
enum class E_AtkType : uint8
{
	None = 0	UMETA(Hidden),
	Melee	UMETA(DisplayName = "Melee"),
	Range	UMETA(DisplayName = "Range"),
	MAX			UMETA(Hidden)
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ENEMYMODULE_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyAttackComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		FName rowName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		E_AtkType AtkType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		TSubclassOf<AActor> bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		FName startSocket;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackSetting")
		FName endSocket;

	// stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackStatSetting")
		float attackDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackStatSetting")
		float attackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAttackStatSetting")
		float attackDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FHitResult m_result;

	class USkeletalMeshComponent* playerMesh;
	class ACharacter* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHit;

	// 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* attackDT;
	// 현재 데이터
	struct FST_SkillData* curAttackData;

	// 데이터들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		E_AtkType d_attackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* d_attackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName d_attackStartPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName d_attackEndPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool d_bLoop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> d_bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float d_delay;

	class USkeletalMeshComponent* mesh;

	// 타이머
	float timer;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void PlayAttack();

	UFUNCTION(BlueprintCallable)
		void EndAttack();

	UFUNCTION(BlueprintCallable)
		void MeleeSense();

	UFUNCTION(BlueprintCallable)
		void RangeAttack();

	UFUNCTION(BlueprintCallable)
		void SetDataTable(FName p_RowName);
};