#pragma once // 중복 컴파일 금지

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h" 
#include "NBC_GameModeBase.generated.h"  // 항상 마지막 선언

UCLASS()
class NBC_PROJECTS04_API ANBC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANBC_GameModeBase();
};