// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveScore.generated.h"

UCLASS()
class FLAPPYBIRD_API USaveScore : public USaveGame
{
	GENERATED_BODY()

public:
	
	USaveScore();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		bool CanAchieveHighScore(int32 inPoint);

	UFUNCTION(BlueprintCallable, Category = "Setters")
		void AddRecord(FText inPlayerName, int32 inPoint);

	UFUNCTION(BlueprintCallable, Category = "Setters")
		void InsertRecord(FText inPlayerName, int32 inPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		TArray<FText> GetNameArray();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		TArray<int32> GetPointArray();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Data")
		TArray<FText>PlayerNames;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
		TArray<int32>PlayerScores;

};
