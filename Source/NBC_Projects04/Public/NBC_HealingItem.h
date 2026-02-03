#pragma once

#include "CoreMinimal.h"
#include "NBC_BaseItem.h"
#include "NBC_HealingItem.generated.h"

UCLASS()
class NBC_PROJECTS04_API ANBC_HealingItem : public ANBC_BaseItem
{
	GENERATED_BODY()

public:
	ANBC_HealingItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Actiator) override;
};