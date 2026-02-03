// Copyright Epic Games, Inc. All Rights Reserved.

#include "NBC_Projects04GameMode.h"
#include "NBC_Projects04Character.h"
#include "UObject/ConstructorHelpers.h"

ANBC_Projects04GameMode::ANBC_Projects04GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
