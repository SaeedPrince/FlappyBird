// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveScore.h"

USaveScore::USaveScore()
{

}

bool USaveScore::CanAchieveHighScore(int32 inPoint)
{
	bool retBool = false;
	if (PlayerScores.Num() > 0)
	{
		for (int32 i = 0; i < PlayerScores.Num(); i++)
		{
			if (inPoint > PlayerScores[i])
			{
				retBool = true;
				break;
			}
		}
	}
	else
	{
		retBool = true;
	}
	return retBool;
}

/*
bool USaveScore::DoesSaveGameExist()
{
	return UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex);
}
*/

TArray<FText> USaveScore::GetNameArray()
{
	return PlayerNames;
}

TArray<int32> USaveScore::GetPointArray()
{
	return PlayerScores;
}

/*
void USaveScore::SaveHighScore(FText inText, int32 inNumber)
{
	if (DoesSaveGameExist())
	{
		int32 iFound = -1;
		for (int32 i = 0; i < PlayerScores.Num(); i++)
		{
			if (inNumber > PlayerScores[i])
			{
				iFound = i;
				break;
			}
		}
		if (iFound != -1)
		{
			PlayerNames.Insert(inText, iFound);
			PlayerScores.Insert(inNumber, iFound);
			while (PlayerNames.Num() > 10)
			{
				PlayerNames.RemoveAt(9);
				PlayerScores.RemoveAt(9);
			}
		}
	}
	else
	{
		PlayerNames.Empty();
		PlayerNames.Init(inText, 1);
		PlayerScores.Empty();
		PlayerScores.Init(inNumber, 1);
	}
	UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}
*/

/*
USaveScore* USaveScore::SaveHighScore()
{
	
}

USaveScore* USaveScore::LoadHighScore()
{
	//return	USaveScore* loaded = Cast<USaveScore>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	return	Cast<USaveScore>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

}
*/

void USaveScore::AddRecord(FText inPlayerName, int32 inPoint)
{
	PlayerNames.Add(inPlayerName);
	PlayerScores.Add(inPoint);
}

void USaveScore::InsertRecord(FText inPlayerName, int32 inPoint)
{
	int32 iFound = -1;
	for (int32 i = 0; i < PlayerScores.Num(); i++)
	{
		if (inPoint > PlayerScores[i])
		{
			iFound = i;
			break;
		}
	}
	if (iFound != -1)
	{
		PlayerNames.Insert(inPlayerName, iFound);
		PlayerScores.Insert(inPoint, iFound);
		while (PlayerNames.Num() > 10)
		{
			PlayerNames.RemoveAt(9);
			PlayerScores.RemoveAt(9);
		}
	}
}
