#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NBC_GameStateBase.generated.h"

USTRUCT(BlueprintType)
struct FNBC_WaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Duration = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemsToSpawn = 50;
};

UCLASS()
class NBC_PROJECTS04_API ANBC_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ANBC_GameStateBase();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void OnPlayerDied();

	UFUNCTION(BlueprintPure, Category = "HUD")
	int32 GetCurrentLevelNumber() const { return CurrentLevelIndex + 1; }

	UFUNCTION(BlueprintPure, Category = "HUD")
	int32 GetCurrentWaveNumber() const { return CurrentWaveIndex + 1; }

	UFUNCTION(BlueprintPure, Category = "HUD")
	float GetRemainingTime() const { return RemainingTime; }

	UFUNCTION(BlueprintPure, Category = "HUD")
	float GetRemainingWaveTime() const { return RemainingTime; }

	UFUNCTION(BlueprintPure, Category = "Wave")
	int32 GetCurrentWaveIndex() const { return CurrentWaveIndex; }

	UFUNCTION(BlueprintPure, Category = "Level")
	int32 GetCurrentLevelIndex() const { return CurrentLevelIndex; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<FNBC_WaveData> Waves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	float RemainingTime = 0.f;

	FTimerHandle WaveEndTimerHandle;
	FTimerHandle RemainingTimeTimerHandle;

	void StartLevel();
	void StartWave();
	void OnWaveTimeUp();
	void TickRemainingTime();

	void EndLevel(bool bClear);
	void RestartCurrentLevel();
	void OpenNextLevel();
};