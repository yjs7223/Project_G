// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASEMODULE_API UBaseStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Attacked(float p_Damage);

	UFUNCTION(BlueprintCallable)
	void Recovery(float p_Recover);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttacked;

};
