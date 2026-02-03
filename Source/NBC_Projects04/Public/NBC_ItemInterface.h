#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NBC_ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNBC_ItemInterface : public UInterface
{
	GENERATED_BODY()
};

class NBC_PROJECTS04_API INBC_ItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;

	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	virtual void ActivateItem(AActor* Actiavtor) = 0;
	virtual FName GetItemType() const = 0;
};
// 순수 가상함수 = 반드시 구현을 해야 함. 오버라이딩 필수.