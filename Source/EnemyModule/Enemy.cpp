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
#include "EnemyDataAsset.h"

AEnemy::AEnemy() : moveSpeed(600)
{
	//enemyAttackComponent = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttackComponent"));

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	controller = Cast<AEnemyController>(GetController());
	ec = FindComponentByClass<UElementComponent>();
	eac = FindComponentByClass<UEnemyAttackComponent>();
	slow = 0.1f;

	if (weaponMesh != nullptr)
	{
		weaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "weapon_r");
	}

	SetDataTable();
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

void AEnemy::SetDataTable()
{
	if (defaultDT != nullptr)
	{
		weaponArr.Empty();
		curDefaultDT = defaultDT->FindRow<FEnemyDataStruct>(*FString::FromInt((int)enemyType), TEXT(""));
		if (curDefaultDT != nullptr)
		{
			moveSpeed = curDefaultDT->moveSpeed;
			eac->attackDamage = curDefaultDT->attackDamage;
			stat->hp = curDefaultDT->hp;

			for (int i = 0; i < curDefaultDT->weaponArr.Num(); i++)
			{
				weaponArr.Add(curDefaultDT->weaponArr[i]);
			}
		}
	}

	if (weaponArr.Num() > 0)
	{
		SetWeaponMesh(weaponArr[0]);
	}
}

void AEnemy::SetWeaponMesh(E_WeaponType p_type)
{
	switch (p_type)
	{
	case E_WeaponType::Sword:
		weaponMesh->SetSkeletalMesh(enemyDA->swordWeaponMesh);
		break;
	case E_WeaponType::Rifle:
		weaponMesh->SetSkeletalMesh(enemyDA->rifleWeaponMesh);
		break;
	}
	
}

