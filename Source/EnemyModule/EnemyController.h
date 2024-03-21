// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYMODULE_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIController)
		bool inSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIController)
		class UBlackboardData* BB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIController)
		class UBehaviorTree* BT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIController)
		class UBehaviorTreeComponent* BT_Component;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

};
