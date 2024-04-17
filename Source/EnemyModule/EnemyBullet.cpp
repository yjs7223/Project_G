// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "BaseStatComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ElementComponent.h"
#include "EnemyAttackComponent.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	bulletMesh->SetupAttachment(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
	bulletMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlapBegin);
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (targetActor == OtherActor)
	{
		if (bBound)
		{
			if (!OtherActor->ActorHasTag("Enemy"))
			{
				return;
			}
		}

		if (UElementComponent* ec = OtherActor->FindComponentByClass<UElementComponent>())
		{
			ec->ChangeElementState2(bulletType);
		}

		if (UBaseStatComponent* sc = OtherActor->FindComponentByClass<UBaseStatComponent>())
		{
			sc->Attacked(bulletDamage);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, OtherActor->GetName());

		if (UEnemyAttackComponent* eac = OtherActor->FindComponentByClass<UEnemyAttackComponent>())
		{
			eac->BoundAttack2(boundCount, maxBoundCount);
		}

		Destroy();
	}
}

