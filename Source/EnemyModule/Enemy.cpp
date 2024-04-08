// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseStatComponent.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAttackComponent.h"

AEnemy::AEnemy() : moveSpeed(600)
{
	//enemyAttackComponent = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttackComponent"));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	ec = Cast<AEnemyController>(GetController());
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HpUpdate();
	MovementUpdate();
	//DieCheck();
}

void AEnemy::HpUpdate()
{
	if (ec != nullptr)
	{
		ec->BBC->SetValueAsFloat("HealthPoint", stat->hp);
	}
}

void AEnemy::MovementUpdate()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void AEnemy::DieCheck()
{
	if (stat->hp <= 0)
	{
		Destroy();
	}
}
