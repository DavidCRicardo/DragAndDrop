// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragAndDropGameMode.h"
#include "DragAndDropCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADragAndDropGameMode::ADragAndDropGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
