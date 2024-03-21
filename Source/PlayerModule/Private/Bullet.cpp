// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Weapon.h"
#include "PlayerCharacter.h"
#include "BaseStatComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	bulletMesh->SetupAttachment(RootComponent);

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	bulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!weapon && OtherActor == weapon && !weapon->pc && OtherActor == weapon->pc)
	{
		return;
	}

	if (UElementComponent* ec = OtherActor->FindComponentByClass<UElementComponent>())
	{
		ec->ChangeElementState(bulletType);
	}

	if (UBaseStatComponent* sc = OtherActor->FindComponentByClass<UBaseStatComponent>())
	{
		sc->Attacked(bulletDamage);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, OtherActor->GetName());

	Destroy();
}

