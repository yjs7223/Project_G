// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	BBC = Blackboard;
	UseBlackboard(BBD, BBC);

}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}