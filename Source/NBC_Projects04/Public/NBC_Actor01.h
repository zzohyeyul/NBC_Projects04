#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "NBC_Actor01.generated.h"

UCLASS()
class NBC_PROJECTS04_API ANBC_Actor01 : public AActor
{
	GENERATED_BODY()
	
public:	
	ANBC_Actor01();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	float MaxRange = 300.f;

	FVector StartLocation;
	FVector MoveDirection = FVector(1, 0, 0);
};
// 이동 플랫폼