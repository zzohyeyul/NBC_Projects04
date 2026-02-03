#include "NBC_Actor01.h"

ANBC_Actor01::ANBC_Actor01()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_AssetPlatform.SM_AssetPlatform"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

void ANBC_Actor01::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void ANBC_Actor01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Current = GetActorLocation();
	FVector OffsetFromStart = Current - StartLocation;

	if (OffsetFromStart.Size() >= MaxRange)
	{
		MoveDirection *= -1.f;
		StartLocation = Current;
	}

	FVector DeltaMove = MoveDirection * MoveSpeed * DeltaTime;
	AddActorWorldOffset(DeltaMove, true);
}
// 이동 플랫폼