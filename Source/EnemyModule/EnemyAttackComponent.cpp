// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "BaseStatComponent.h"
#include "Engine/World.h"
#include "ST_AttackData.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "ActiveZone.h"
#include "ElementComponent.h"
#include "EnemyBullet.h"
#include "CollisionQueryParams.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyDataAsset.h"

// Sets default values for this component's properties
UEnemyAttackComponent::UEnemyAttackComponent() : maxDis(600)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bHit = true;
	// ...
}


// Called when the game starts
void UEnemyAttackComponent::BeginPlay()
{
	Super::BeginPlay(); 

	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) != NULL)
	{
		player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}
	if (player != NULL)
	{
		playerMesh = player->FindComponentByClass<USkeletalMeshComponent>();
	}
	mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	ec = GetOwner()->FindComponentByClass<UElementComponent>();
}


// Called every frame
void UEnemyAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bHit)
	{
		timer -= DeltaTime;
		if (timer <= 0)
		{
			switch (AtkType)
			{
			case E_AtkType::Melee:
				MeleeSense();
				break;
			case E_AtkType::Range:
				RangeAttack();
				break;
			}
		}
	}

}

void UEnemyAttackComponent::PlayAttack()
{
	bHit = false;
	timer = d_delay;
}

void UEnemyAttackComponent::EndAttack()
{
	bHit = true;
}

void UEnemyAttackComponent::MeleeSense()
{
	FCollisionQueryParams traceParams;

	FVector rStart = mesh->GetSocketLocation("R_Attack_Socket_Start");
	FVector rEnd = mesh->GetSocketLocation("R_Attack_Socket_End");

	FVector lStart = mesh->GetSocketLocation("L_Attack_Socket_Start");
	FVector lEnd = mesh->GetSocketLocation("L_Attack_Socket_End");

	if (GetWorld()->LineTraceSingleByChannel(m_result, rStart, rEnd, ECC_Visibility, traceParams))
	{
		if (m_result.GetActor()->ActorHasTag("Player"))
		{
			UBaseStatComponent* stat = m_result.GetActor()->FindComponentByClass<UBaseStatComponent>();
			stat->Attacked(attackDamage);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Hit!")));
			bHit = true;
			return;
		}
	}

	if (GetWorld()->LineTraceSingleByChannel(m_result, lStart, lEnd, ECC_Visibility, traceParams))
	{
		if (m_result.GetActor()->ActorHasTag("Player"))
		{
			UBaseStatComponent* stat = m_result.GetActor()->FindComponentByClass<UBaseStatComponent>();
			stat->Attacked(attackDamage);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Hit!")));
			bHit = true;
			return;
		}
	}
}

void UEnemyAttackComponent::RangeAttack()
{
	FVector start = mesh->GetSocketLocation(endSocket);
	FVector end = player->GetActorLocation() + FVector(0, 0, 70);
	FRotator rot = (end - start).Rotation();

	FActorSpawnParameters spawnParam;
	AActor* cpybullet = GetWorld()->SpawnActor<AActor>(d_bullet, start, rot, spawnParam);

	bHit = true;
}

void UEnemyAttackComponent::BoundAttack()
{
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(GetOwner());

	FVector start = GetOwner()->GetActorLocation();

	AEnemy* owner = Cast<AEnemy>(GetOwner());

	float dis = maxDis;	// 최대거리
	AEnemy* e = nullptr;

	int i = 0;

	while (i <= 5)
	{
		if (owner->az != nullptr)
		{
			for (auto& enemy : owner->az->enemyArray)
			{
				if (GetWorld()->LineTraceSingleByChannel(m_result, start, enemy->GetActorLocation(), ECC_Visibility, traceParams))
				{
					if (m_result.GetActor() == enemy)
					{
						if (Cast<AEnemy>(enemy)->GetDistanceTo(owner) <= maxDis)
						{
							if (Cast<AEnemy>(enemy)->ec->stack == i)
							{
								if (Cast<AEnemy>(enemy)->GetDistanceTo(owner) <= dis)
								{
									dis = Cast<AEnemy>(enemy)->GetDistanceTo(owner);
									e = Cast<AEnemy>(enemy);
								}
							}
						}
					}
				}
			}
		}

		if (e == nullptr)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	if (e != nullptr)
	{
		FVector end = e->GetActorLocation();
		FRotator rot = (end - start).Rotation();

		FActorSpawnParameters spawnParam;
		AActor* cpybullet = GetWorld()->SpawnActor<AActor>(bullet, start, rot, spawnParam);
		AEnemyBullet* ebullet = Cast<AEnemyBullet>(cpybullet);
		
		ebullet->bBound = true;
		ebullet->bulletType = EElementTypeEnum::ET_Air;
		ebullet->bulletDamage = 10;

		ebullet->maxBoundCount = 3 * ec->stack;

		ebullet->boundCount = 1;
		ebullet->targetActor = e;
	}
}

void UEnemyAttackComponent::BoundAttack2(int p_boundCount, int p_maxBoundCount)
{
	FCollisionQueryParams traceParams;
	traceParams.AddIgnoredActor(GetOwner());

	FVector start = GetOwner()->GetActorLocation();

	AEnemy* owner = Cast<AEnemy>(GetOwner());

	float dis = maxDis;	// 최대거리
	AEnemy* e = nullptr;

	int i = 0;

	while (i <= 5)
	{
		for (auto& enemy : owner->az->enemyArray)
		{
			if (GetWorld()->LineTraceSingleByChannel(m_result, start, enemy->GetActorLocation(), ECC_Visibility, traceParams))
			{
				if (m_result.GetActor() == enemy)
				{
					if (Cast<AEnemy>(enemy)->GetDistanceTo(owner) <= maxDis)
					{
						if (Cast<AEnemy>(enemy)->ec->stack == i)
						{
							if (Cast<AEnemy>(enemy)->GetDistanceTo(owner) <= dis)
							{
								dis = Cast<AEnemy>(enemy)->GetDistanceTo(owner);
								e = Cast<AEnemy>(enemy);
							}
						}
					}
				}
			}
		}

		if (e == nullptr)
		{
			i++;
		}
		else
		{
			break;
		}
	}

	if (e != nullptr)
	{
		if (p_boundCount <= p_maxBoundCount)
		{
			FVector end = e->GetActorLocation();
			FRotator rot = (end - start).Rotation();

			FActorSpawnParameters spawnParam;
			AActor* cpybullet = GetWorld()->SpawnActor<AActor>(bullet, start, rot, spawnParam);
			AEnemyBullet* ebullet = Cast<AEnemyBullet>(cpybullet);

			ebullet->bBound = true;
			ebullet->bulletType = EElementTypeEnum::ET_Air;
			//ebullet->projectileMovement->HomingTargetComponent = e;

			ebullet->maxBoundCount = p_maxBoundCount;
			ebullet->boundCount = p_boundCount;
			ebullet->bulletDamage = 10;

			ebullet->boundCount++;
			ebullet->targetActor = e;
		}
	}
}

void UEnemyAttackComponent::SetDataTable(FName p_RowName)
{
	if (attackDT != nullptr)
	{
		curAttackData = attackDT->FindRow<FST_SkillData>(p_RowName, TEXT(""));
		if (curAttackData != nullptr)
		{
			d_attackMontage.Empty();
			for (int i = 0; i < curAttackData->attackMontage.Num(); i++)
			{
				d_attackMontage.Add(curAttackData->attackMontage[i]);
			}

			d_attackType = curAttackData->attackType;
			//d_attackMontage = curAttackData->attackMontage;
			d_rightHand = curAttackData->rightHand;
			d_leftHand = curAttackData->leftHand;
			d_bLoop = curAttackData->bLoop;
			d_bullet = curAttackData->bullet;
			d_delay = curAttackData->delay;
		}
	}
}