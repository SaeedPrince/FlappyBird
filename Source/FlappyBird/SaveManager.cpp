// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveManager.h"
#include "SaveScore.h"
#include "UswgRegister.h"
#include "Kismet/GameplayStatics.h"

USaveManager::USaveManager()
{
	SaveSlotName = TEXT("HighScore");
	UserIndex = 0;
}

bool USaveManager::CanAchieveHighScore(int32 inPoint)
{
	return SaveRef->CanAchieveHighScore(inPoint);
}

void USaveManager::SetReferences(UUswgRegister* inRef, TSubclassOf<USaveScore> inSub)
{
	if (IsValid(inRef))
	{
		RegisterRef = inRef;
		RegisterRef->OnPlayerNameRegister.AddDynamic(this, &USaveManager::SaveHighScore);
		if (IsValid(inSub))
		{
			SaveScoreBP = inSub;
			if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
			{
				USaveScore* Svgm = Cast<USaveScore>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
				if (IsValid(Svgm))
				{
					SaveRef = Svgm;
				}
			}
			else
			{
				USaveScore* Svgm = Cast<USaveScore>(UGameplayStatics::CreateSaveGameObject(SaveScoreBP));
				if (IsValid(Svgm))
				{
					SaveRef = Svgm;
				}
			}
		}
	}
}

void USaveManager::LoadHighScore(TArray<FText>& txtArray, TArray<int32>& intArray)
{
	if (IsValid(SaveRef))
	{
		txtArray = SaveRef->GetNameArray();
		intArray = SaveRef->GetPointArray();
	}
}


void USaveManager::SaveHighScore(FText inPlayerName, int32 inPoint)
{
	if (IsValid(SaveRef))
	{
		if (SaveRef->GetNameArray().Num() > 0)
		{
			SaveRef->InsertRecord(inPlayerName, inPoint);
		}
		else
		{
			SaveRef->AddRecord(inPlayerName, inPoint);
		}
		UGameplayStatics::SaveGameToSlot(SaveRef, SaveSlotName, UserIndex);
	}
}