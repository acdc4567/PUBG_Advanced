// Copyright Epic Games, Inc. All Rights Reserved.

#include "PUBG_AdvancedGameMode.h"
#include "PUBG_AdvancedCharacter.h"
#include "UObject/ConstructorHelpers.h"

APUBG_AdvancedGameMode::APUBG_AdvancedGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
