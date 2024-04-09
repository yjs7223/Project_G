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

// Sets default values for this component's properties
UEnemyAttackComponent::UEnemyAttackComponent()
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
}

void UEnemyAttackComponent::EndAttack()
{
	bHit = true;
}

void UEnemyAttackComponent::MeleeSense()
{
	FCollisionQueryParams traceParams;

	FVector start = mesh->GetSocketLocation(d_attackStartPoint);
	FVector end = mesh->GetSocketLocation(d_attackEndPoint);

	if (GetWorld()->LineTraceSingleByChannel(m_result, start, end, ECC_Visibility, traceParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Hit!")));
		if (m_result.GetActor()->ActorHasTag("Player"))
		{
			UBaseStatComponent* stat = m_result.GetActor()->FindComponentByClass<UBaseStatComponent>();
			stat->Attacked(attackDamage);
			bHit = true;
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

void UEnemyAttackComponent::SetDataTable(FName p_RowName)
{
	if (attackDT != nullptr)
	{
		curAttackData = attackDT->FindRow<FST_SkillData>(p_RowName, TEXT(""));
		if (curAttackData != nullptr)
		{
			d_attackType = curAttackData->attackType;
			d_attackMontage = curAttackData->attackMontage;
			d_attackStartPoint = curAttackData->attackStartPoint;
			d_attackEndPoint = curAttackData->attackEndPoint;
			d_bLoop = curAttackData->bLoop;
			d_bullet = curAttackData->bullet;
			d_delay = curAttackData->delay;
		}
	}
}