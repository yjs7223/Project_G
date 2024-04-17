// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementComponent.h"
#include "EnemyBullet.generated.h"

UCLASS()
class ENEMYMODULE_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* bulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* projectileMovement;

	//데미지변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float bulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EElementTypeEnum bulletType;

	bool bBound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* targetActor;
	int boundCount;
	int maxBoundCount;
};
