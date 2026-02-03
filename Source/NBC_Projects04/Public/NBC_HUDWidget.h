#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NBC_HUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
class ANBC_GameStateBase;
class ANBC_Projects04Character;

UCLASS()
class NBC_PROJECTS04_API UNBC_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveNum;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Timer;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HP;

private:
	UPROPERTY()
	ANBC_GameStateBase* GS;

	UPROPERTY()
	ANBC_Projects04Character* Player;

	void RefreshHUD();
};