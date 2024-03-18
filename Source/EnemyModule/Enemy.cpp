// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseStatComponent.h"

AEnemy::AEnemy() : moveSpeed(600)
{

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementSetting();
	//DieCheck();
}

void AEnemy::MovementSetting()
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
