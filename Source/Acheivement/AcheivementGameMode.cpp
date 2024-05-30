// Copyright Epic Games, Inc. All Rights Reserved.

#include "AcheivementGameMode.h"
#include "AcheivementCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAcheivementGameMode::AAcheivementGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	ach_list = NewObject<UAchieveList>();
}
