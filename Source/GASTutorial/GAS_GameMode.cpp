// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAS_GameMode.h"
#include "GAS_Character.h"
#include "UObject/ConstructorHelpers.h"

AGAS_GameMode::AGAS_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
