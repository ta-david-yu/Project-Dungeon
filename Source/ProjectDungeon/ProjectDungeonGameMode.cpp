// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectDungeonGameMode.h"
#include "ProjectDungeonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDungeonGameMode::AProjectDungeonGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
