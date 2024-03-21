// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementComponent.h"
#include "Bullet.generated.h"

UCLASS()
class PLAYERMODULE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* bulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* projectileMovement;

	class AWeapon* weapon;

	//���������� ����Ÿ�Ժ��� �߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bulletDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementTypeEnum bulletType;
};
