// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UEnemyAttackComponent::UEnemyAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyAttackComponent::CloseRangeAttack()
{
	FVector start = GetOwner()->GetActorLocation() + FVector(0, 0, 50);
	FVector end = start + GetOwner()->GetActorForwardVector() * attackRange;
	FRotator rot = GetOwner()->GetActorForwardVector().Rotation();
	TArray<AActor*> a;

	FCollisionQueryParams traceParams;
	
	if (UKismetSystemLibrary::BoxTraceSingle(GetWorld(), start, end, FVector(50, 50, 50), rot, TraceTypeQuery1, false, a, EDrawDebugTrace::ForDuration, m_result, true))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Hit!")));
	}

}

void UEnemyAttackComponent::LongRangeAttack()
{
	FVector start = GetOwner()->GetActorLocation() + FVector(0, 0, 50);
	FVector end = start + GetOwner()->GetActorForwardVector() * attackRange;
	FRotator rot = GetOwner()->GetActorForwardVector().Rotation();
	TArray<AActor*> a;

	FCollisionQueryParams traceParams;
}

