// Fill out your copyright notice in the Description page of Project Settings.


#include "AchieveList.h"

UAchieveList::UAchieveList()
{
	Load();
	Init();
}

UAchieveList::~UAchieveList()
{
	Save();
}

void UAchieveList::Save()
{
	const FString FilePath = FPaths::ProjectSavedDir() + "achievment_save.txt";

	FArchive* Ar = IFileManager::Get().CreateFileWriter(*FilePath);
	if (Ar)
	{
		int32 NumAchieves = _achievments.Num();
		*Ar << NumAchieves;

		for (FAchieve& Achieve : _achievments)
		{
			FString name = Achieve.name.ToString();
			*Ar << name;
			*Ar << Achieve.val;
			int32 AchType = static_cast<int32>(Achieve.ach_type);
			*Ar << AchType;
			*Ar << Achieve.passed;
		}
		delete Ar;
	}
}

void UAchieveList::Load()
{
	FString FilePath = FPaths::ProjectSavedDir() + "achievment_save.txt";

	FArchive* Ar = IFileManager::Get().CreateFileReader(*FilePath);
	if (Ar)
	{
		int32 NumAchieves = 0;
		*Ar << NumAchieves;

		_achievments.Empty();
		_achievments.Reserve(NumAchieves);

		for (int32 i = 0; i < NumAchieves; ++i)
		{
			FAchieve Achieve;
			FString name;
			*Ar << name;
			Achieve.name = FName(name);
			*Ar << Achieve.val;
			int32 AchType;
			*Ar << AchType;
			Achieve.ach_type = static_cast<type>(AchType);
			*Ar << Achieve.passed;

			_achievments.Add(Achieve);
		}
		delete Ar;
	}
}

void UAchieveList::Init()
{
	if (_achievments.Num()) {
		return;
	}

	_achievments = {
		{ FName("Run 10 meters"),	10,		type::Run,		false },
		{ FName("Run 50 meters"),	50,		type::Run,		false },
		{ FName("Run 100 meters"),	100,	type::Run,		false },
		{ FName("Jump 1 time"),		1,		type::Jump,		false },
		{ FName("Jump 5 times"),	5,		type::Jump,		false },
		{ FName("Jump 15 times"),	15,		type::Jump,		false },
		{ FName("Trigger 1"),		1,		type::Trigger,	false },
		{ FName("Trigger 2"),		1,		type::Trigger,	false },
		{ FName("Trigger 3"),		1,		type::Trigger,	false }
	};
}

FAchieve* UAchieveList::FindAchieveByName(const FName& name)
{
	return _achievments.FindByPredicate([=](const FAchieve& ach) {
		return ach.name == name;
		});
}

TMap<FName, bool> UAchieveList::GetAllAchievementsNameAndState()
{
	TMap<FName, bool> achives;

	for (const auto& ach : _achievments) {
		achives.Add(ach.name, ach.passed);
	}
	return achives;
}

bool UAchieveList::CheckAchieveState(const FName& name)
{
	FAchieve* achieve = FindAchieveByName(name);

	return achieve ? achieve->passed : false;
}

bool UAchieveList::CheckAchievePassed(const FName& name, const int32 val)
{
	FAchieve* achieve = FindAchieveByName(name);

	if (!achieve) {
		return false;
	}
	else if (achieve->passed) {
		return true;
	}
	if (achieve->val <= val) {
		achieve->passed = true;
		return true;
	}

	return false;
}
