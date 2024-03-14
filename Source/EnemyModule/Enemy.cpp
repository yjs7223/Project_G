// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

void AEnemy::MovementSetting()
{
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}
