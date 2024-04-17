// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveZone.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "EnemyController.h"

// Sets default values
AActiveZone::AActiveZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("C Mesh"));
	RootComponent = collisionMesh;
}

// Called when the game starts or when spawned
void AActiveZone::BeginPlay()
{
	Super::BeginPlay();

	collisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AActiveZone::OnOverlapBegin);
}

// Called every frame
void AActiveZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemySet();
}

void AActiveZone::EnemySet()
{
	this->GetOverlappingActors(enemyArray, AEnemy::StaticClass());
}

void AActiveZone::EnemyActive()
{
	for (auto& enemy : enemyArray)
	{
		Cast<AEnemy>(enemy)->controller->bbc->SetValueAsBool("ActiveClass", true);
		Cast<AEnemy>(enemy)->az = this;
	}
}

void AActiveZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		EnemyActive();
	}
}

