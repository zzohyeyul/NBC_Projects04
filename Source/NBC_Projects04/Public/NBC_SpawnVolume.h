#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NBC_ItemSpawnRow.h"
#include "NBC_SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class NBC_PROJECTS04_API ANBC_SpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ANBC_SpawnVolume();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
    UDataTable* ItemDataTable;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnRandomItem();

    FVector GetRandomPointInVolume() const;
    void SpawnItem(TSubclassOf<AActor> ItemClass);
    FNBC_ItemSpawnRow* GetRandomItem() const;

    void SetSpawnLevelIndex(int32 InLevelIndex) { SpawnLevelIndex = InLevelIndex; }

protected:
    UPROPERTY()
    int32 SpawnLevelIndex = 0;
};