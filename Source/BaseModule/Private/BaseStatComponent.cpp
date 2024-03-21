// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatComponent.h"

// Sets default values for this component's properties
UBaseStatComponent::UBaseStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	maxHp = 100.f;
	// ...
}


// Called when the game starts
void UBaseStatComponent::BeginPlay()
{
	Super::BeginPlay();
	hp = maxHp;
	// ...
	
}


// Called every frame
void UBaseStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseStatComponent::Attacked(float p_Damage)
{
	bAttacked = true;

	hp -= p_Damage;

	if (hp < 0.f)
	{
		hp = 0;
	}
}

void UBaseStatComponent::Recovery(float p_Recover)
{
	hp += p_Recover;

	if (hp > maxHp)
	{
		hp = maxHp;
	}
}

