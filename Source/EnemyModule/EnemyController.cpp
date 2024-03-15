// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackboardComp = Blackboard;
	UseBlackboard(BB, BlackboardComp);

}

void AEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}