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

	// 현재 웨이브
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int curWave;

	// 스폰 관련 데이터 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UDataTable* spawnData;
	// 현재 데이터 테이블
	struct FST_Spawner* curSpawnData;

	// 트리거 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bTriggerOn;

	// 스포너 활성화 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		bool bCheckEnable;

	// 플레이어가 사살한 적의 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		int countKill;

	// 웨이브 생성 후 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float countSeconds;

	// 딜레이용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		float spawnTimer;
	// 스폰할 적
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> CloseRangeEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		TSubclassOf<APawn> LongRangeEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnerSetting")
		class UBehaviorTree* BT_Enemy;

	class AEnemyController* EnemyController;

	// 이번 웨이브 소환 여부
	bool bSpawnCheck;

	// 이번 웨이브에 소환 한 수
	int rifleCount;
	int sniperCount;

	// 스포너 스폰 지점들
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

	// 데이터 테이블 정보
	bool lastSpawn;
	float spawnCondition;
	float spawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int spawnSpot;
	enum ESpawnType spawnType;
	TMap<enum EEnemyName, int> spawnWave;

	bool waveEnd;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 웨이브 스폰
	void SpawnWave();

	// 웨이브 컨트롤
	void WaveControl(const float DeltaTime);

	// 스폰 지점 검사 후 변경
	int SetSpawnSpot(int m_Spawn_Pos);

	// 다음 웨이브 이동 및 초기화
	void NextWave();

	// 스포너 활/비활성화
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnEnable(bool p_flag);
	UFUNCTION()
		void TriggerOnTrue();
	void SetDataTable(int p_curWave);
};
