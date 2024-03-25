// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ST_Spawn.h"
#include "EnemySpawner.generated.h"

UCLASS()
class ENEMYMODULE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// ���� ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int curWave;

	// ���� ���� ������ ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* spawnData;
	// ���� ������ ���̺�
	struct FST_Spawner* curSpawnData;

	// ���� ������ Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool many_Spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool TriggerOn;

	// ������ Ȱ��ȭ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		bool check_Overlap;

	// �÷��̾ ����� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		int count_Kill;

	// ���̺� ���� �� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float count_Seconds;

	// �����̿�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawn_Timer;
	// ������ ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> CloseRangeEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> LongRangeEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		class UBehaviorTree* BT_Enemy;

	class AEnemyController* EnemyController;

	// �̹� ���̺� ��ȯ ����
	bool spawnCheck;

	// �̹� ���̺꿡 ��ȯ �� ��
	int rifleCount;
	int sniperCount;

	// ������ ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> spawn_Spots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		TSubclassOf<AActor> lastPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		float pointTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		int Total_EnemyNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		bool pointSpawnCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		ACharacter* player;

	// LastPoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPointSetting")
		AActor* cpyLastPoint;

	// ������ ���̺� ����
	bool last_Spawn;
	float spawn_Condition;
	float spawn_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawn_Spot;
	enum Spawn_Type spawn_Type;
	TMap<enum Enemy_Name, int> spawn_Wave;

	bool waveEnd;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���̺� ����
	void SpawnWave();

	// ���̺� ��Ʈ��
	void WaveControl(const float DeltaTime);

	// ���� ���� �˻� �� ����
	int SetSpawnSpot(int m_Spawn_Pos);

	// ���� ���̺� �̵� �� �ʱ�ȭ
	void NextWave();

	// ������ Ȱ/��Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnEnable(bool p_flag);
	UFUNCTION()
		void TriggerOnTrue();
	void SetDataTable(int p_curWave);
};
