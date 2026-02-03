#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBC_Actor02.generated.h"

class UStaticMeshComponent;

UCLASS()
class NBC_PROJECTS04_API ANBC_Actor02 : public AActor
{
	GENERATED_BODY()
	
public:	
	ANBC_Actor02();

protected:
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	float RotationSpeed = 100.f;
};
// 회전 물체