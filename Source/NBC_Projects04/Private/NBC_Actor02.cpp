#include "NBC_Actor02.h"

ANBC_Actor02::ANBC_Actor02()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetMobility(EComponentMobility::Movable);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Statue.SM_Statue"));
	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

void ANBC_Actor02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator DeltaRot(0.f, RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(DeltaRot);
}
// 회전 물체