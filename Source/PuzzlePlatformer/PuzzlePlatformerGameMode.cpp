// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformerGameMode.h"
#include "PuzzlePlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePlatformerGameMode::APuzzlePlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ensures that this code is only called once - optimisation at run time
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
