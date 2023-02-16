// Copyright Epic Games, Inc. All Rights Reserved.

#include "Group6ix_MondayGameMode.h"
#include "Group6ix_MondayCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGroup6ix_MondayGameMode::AGroup6ix_MondayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
