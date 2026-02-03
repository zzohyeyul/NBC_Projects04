#include "NBC_HUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "NBC_GameStateBase.h"
#include "NBC_Projects04/NBC_Projects04Character.h"

void UNBC_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GS = GetWorld() ? GetWorld()->GetGameState<ANBC_GameStateBase>() : nullptr;
	Player = Cast<ANBC_Projects04Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	RefreshHUD();
}

void UNBC_HUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	RefreshHUD();
}

void UNBC_HUDWidget::RefreshHUD()
{
	if (!GS || !Player) return;

	if (WaveNum)
	{
		const int32 Wave = GS->GetCurrentWaveIndex() + 1;
		const int32 Level = GS->GetCurrentLevelIndex() + 1;

		WaveNum->SetText(
			FText::FromString(
				FString::Printf(TEXT("Wave %d OF Level %d"), Wave, Level)
			)
		);
	}

	if (Timer)
	{
		const float Remain = GS->GetRemainingTime();
		Timer->SetText(FText::FromString(FString::Printf(TEXT("Time : %.0f sec"), Remain)));
	}

	if (HP)
	{
		const float Ratio = Player->GetHealth() / Player->GetMaxHealth();
		HP->SetPercent(Ratio);
	}
}