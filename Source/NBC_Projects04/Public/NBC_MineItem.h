#pragma once

#include "CoreMinimal.h"
#include "NBC_BaseItem.h"
#include "NBC_MineItem.generated.h"

UCLASS()
class NBC_PROJECTS04_API ANBC_MineItem : public ANBC_BaseItem
{
	GENERATED_BODY()

public:
	ANBC_MineItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();
};