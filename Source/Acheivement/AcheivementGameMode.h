// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AchieveList.h"
#include "GameFramework/GameModeBase.h"
#include "AcheivementGameMode.generated.h"

UCLASS(minimalapi)
class AAcheivementGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAcheivementGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Achievements)
	UAchieveList* ach_list;
};
