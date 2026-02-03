#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "NBC_ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FNBC_ItemSpawnRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LevelIndex = 0;
};