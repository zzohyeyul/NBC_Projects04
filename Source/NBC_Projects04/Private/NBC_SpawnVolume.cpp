#include "NBC_SpawnVolume.h"
#include "NBC_GameInstance.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ANBC_SpawnVolume::ANBC_SpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    ItemDataTable = nullptr;
}

void ANBC_SpawnVolume::SpawnRandomItem()
{
    if (FNBC_ItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            SpawnItem(ActualClass);
        }
    }
}

FVector ANBC_SpawnVolume::GetRandomPointInVolume() const
{
    FVector Ext = SpawningBox->GetScaledBoxExtent();
    FVector Origin = SpawningBox->GetComponentLocation();

    const float X = FMath::FRandRange(-Ext.X, Ext.X);
    const float Y = FMath::FRandRange(-Ext.Y, Ext.Y);

    const float ZMin = -Ext.Z;
    const float ZMax = FMath::Min(Ext.Z, 500.f);
    const float Z = FMath::FRandRange(ZMin, ZMax);

    return Origin + FVector(X, Y, Z);
}

FNBC_ItemSpawnRow* ANBC_SpawnVolume::GetRandomItem() const
{
    if (!ItemDataTable) return nullptr;

    TArray<FNBC_ItemSpawnRow*> AllRows;
    static const FString ContextString(TEXT("ItemSpawnContext"));
    ItemDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    TArray<FNBC_ItemSpawnRow*> FilteredRows;
    for (FNBC_ItemSpawnRow* Row : AllRows)
    {
        if (Row && Row->LevelIndex == SpawnLevelIndex)
        {
            FilteredRows.Add(Row);
        }
    }

    if (FilteredRows.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No items for LevelIndex %d"), SpawnLevelIndex);
        return nullptr;
    }

    float TotalChance = 0.f;
    for (const FNBC_ItemSpawnRow* Row : FilteredRows)
    {
        TotalChance += Row->SpawnChance;
    }

    const float RandValue = FMath::FRandRange(0.f, TotalChance);
    float Acc = 0.f;

    for (FNBC_ItemSpawnRow* Row : FilteredRows)
    {
        Acc += Row->SpawnChance;
        if (RandValue <= Acc)
        {
            return Row;
        }
    }

    return nullptr;
}

void ANBC_SpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass) return;

    GetWorld()->SpawnActor<AActor>(
        ItemClass,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator
    );
}