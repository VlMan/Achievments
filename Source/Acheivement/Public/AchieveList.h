// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AchieveList.generated.h"

/**
 * 
 */

UENUM()
enum class type {
	Unknown = 0,
	Run,
	Jump,
	Trigger
};

USTRUCT(BlueprintType)
struct FAchieve {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName name = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 val = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	type ach_type = type::Unknown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool passed = false;
};

UCLASS()
class UAchieveList : public UObject
{
	GENERATED_BODY()

public:
	UAchieveList();
	~UAchieveList();

	void Save();
	void Load();

	void Init();

	UFUNCTION(BlueprintCallable, Category = "Achievements")
	bool CheckAchieveState(const FName& name);

	UFUNCTION(BlueprintCallable, Category = "Achievements")
	bool CheckAchievePassed(const FName& name, const int32 val);

	UFUNCTION(BlueprintCallable, Category = "Achievements")
	TMap<FName, bool> GetAllAchievementsNameAndState();

	UFUNCTION(BlueprintCallable, Category = "Achievements")
	TArray<FAchieve> GetAllAchievements() { return _achievments; }

protected:
	FAchieve* FindAchieveByName(const FName& name);

private:
	TArray<FAchieve> _achievments;
};
