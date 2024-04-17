// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseStatComponent.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAttackComponent.h"
#include "ElementComponent.h"
#include "ActiveZone.h"

AEnemy::AEnemy() : moveSpeed(600)
{
	//enemyAttackComponent = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttackComponent"));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<AEnemyController>(GetController());
	ec = FindComponentByClass<UElementComponent>();
	eac = FindComponentByClass<UEnemyAttackComponent>();
	slow = 0.1f;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElementalEffect(DeltaTime);
	HpUpdate();
	MovementUpdate();
	//DieCheck();
}

void AEnemy::HpUpdate()
{
	if (controller != nullptr)
	{
		controller->bbc->SetValueAsFloat("HealthPoint", stat->hp);
	}
}

void AEnemy::MovementUpdate()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed - moveSpeed * (ec->stack * slow);;

	// 표시용
	curSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AEnemy::DieCheck()
{
	if (stat->hp <= 0)
	{
		Destroy();
	}
}

void AEnemy::ElementalEffect(float t)
{
	if (ec != nullptr)
	{
		switch (ec->ElementState)
		{
		case EElementTypeEnum::ET_Normal:
			eTimer = 0;
			ec->stack = 0;
			break;
		case EElementTypeEnum::ET_Flame:
			eTimer += t;
			if (eTimer >= 0.5f)
			{
				stat->hp -= 3 * ec->stack;
				eTimer = 0;
			}
			break;
		case EElementTypeEnum::ET_Water:
			// 공백
			break;
		case EElementTypeEnum::ET_Air:
			if (ec->bBound)
			{
				eac->BoundAttack();
				ec->bBound = false;
			}
			// 공백
			break;
		case EElementTypeEnum::ET_Evaporation:
			break;
		case EElementTypeEnum::ET_Diffusion:
			break;
		case EElementTypeEnum::ET_Florescence:
			break;
		}
	}
}

