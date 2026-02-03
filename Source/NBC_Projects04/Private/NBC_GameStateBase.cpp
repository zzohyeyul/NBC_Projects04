#include "NBC_GameStateBase.h"

#include "NBC_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "NBC_SpawnVolume.h"
#include "NBC_Projects04/NBC_Projects04Character.h"

ANBC_GameStateBase::ANBC_GameStateBase()
{
	Waves = { {40.f, 70}, {30.f, 80}, {20.f, 90} };
}

void ANBC_GameStateBase::BeginPlay()
{
	Super::BeginPlay();

	if (UNBC_GameInstance* GI = GetGameInstance<UNBC_GameInstance>())
	{
		CurrentLevelIndex = GI->CurrentLevelIndex;
	}

	StartLevel();
}

void ANBC_GameStateBase::StartLevel()
{
	CurrentWaveIndex = 0;
	StartWave();
}

void ANBC_GameStateBase::StartWave()
{
	GetWorldTimerManager().ClearTimer(WaveEndTimerHandle);
	GetWorldTimerManager().ClearTimer(RemainingTimeTimerHandle);

	if (!Waves.IsValidIndex(CurrentWaveIndex))
	{
		EndLevel(true);
		OpenNextLevel();
		return;
	}

	const FNBC_WaveData& Wave = Waves[CurrentWaveIndex];
	RemainingTime = Wave.Duration;

	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start! (Level %d) (%.0f sec, Spawn %d)"),
		CurrentWaveIndex + 1,
		CurrentLevelIndex + 1,
		Wave.Duration,
		Wave.ItemsToSpawn
	);

	TArray<ANBC_SpawnVolume*> Volumes;
	for (TActorIterator<ANBC_SpawnVolume> It(GetWorld()); It; ++It)
	{
		Volumes.Add(*It);
	}

	if (Volumes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No SpawnVolume found in this level."));
		return;
	}

	for (ANBC_SpawnVolume* V : Volumes)
	{
		V->SetSpawnLevelIndex(CurrentLevelIndex);
	}

	for (int32 i = 0; i < Wave.ItemsToSpawn; ++i)
	{
		const int32 Pick = FMath::RandRange(0, Volumes.Num() - 1);
		Volumes[Pick]->SpawnRandomItem();
	}

	GetWorldTimerManager().SetTimer(
		WaveEndTimerHandle,
		this,
		&ANBC_GameStateBase::OnWaveTimeUp,
		Wave.Duration,
		false
	);

	GetWorldTimerManager().SetTimer(
		RemainingTimeTimerHandle,
		this,
		&ANBC_GameStateBase::TickRemainingTime,
		0.1f,
		true
	);
}

void ANBC_GameStateBase::TickRemainingTime()
{
	RemainingTime -= 0.1f;
	if (RemainingTime < 0.f)
	{
		RemainingTime = 0.f;
	}
}

void ANBC_GameStateBase::OnWaveTimeUp()
{
	GetWorldTimerManager().ClearTimer(RemainingTimeTimerHandle);
	RemainingTime = 0.f;

	ANBC_Projects04Character* Player =
		Cast<ANBC_Projects04Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Player || Player->GetHealth() <= 0.f)
	{
		EndLevel(false);
		RestartCurrentLevel();
		return;
	}

	CurrentWaveIndex++;
	StartWave();
}

void ANBC_GameStateBase::OnPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Over - Player Died"));

	GetWorldTimerManager().ClearTimer(WaveEndTimerHandle);
	GetWorldTimerManager().ClearTimer(RemainingTimeTimerHandle);

	RestartCurrentLevel();
}

void ANBC_GameStateBase::EndLevel(bool bClear)
{
	GetWorldTimerManager().ClearTimer(WaveEndTimerHandle);
	GetWorldTimerManager().ClearTimer(RemainingTimeTimerHandle);

	if (bClear)
	{
		UE_LOG(LogTemp, Warning, TEXT("Level Clear!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over! Restarting..."));
	}
}

void ANBC_GameStateBase::RestartCurrentLevel()
{
	const FName CurrentMap = FName(*UGameplayStatics::GetCurrentLevelName(this, true));
	UGameplayStatics::OpenLevel(this, CurrentMap);
}

void ANBC_GameStateBase::OpenNextLevel()
{
	if (LevelMapNames.IsEmpty())
	{
		RestartCurrentLevel();
		return;
	}

	CurrentLevelIndex++;

	if (!LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		CurrentLevelIndex = 0;
	}

	if (UNBC_GameInstance* GI = GetGameInstance<UNBC_GameInstance>())
	{
		GI->CurrentLevelIndex = CurrentLevelIndex;
	}

	UGameplayStatics::OpenLevel(this, LevelMapNames[CurrentLevelIndex]);
}