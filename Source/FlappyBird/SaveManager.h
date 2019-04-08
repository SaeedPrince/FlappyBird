// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.generated.h"

class USaveScore;
class UUswgRegister;

UCLASS()
class FLAPPYBIRD_API USaveManager : public UObject
{
	GENERATED_BODY()
	
public:

	// Consructor
	USaveManager();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		bool CanAchieveHighScore(int32 inPoint);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		void LoadHighScore(TArray<FText>& txtArray, TArray<int32>& intArray);

	UFUNCTION(BlueprintCallable, Category = "Events")
		void SetReferences(class UUswgRegister* inRef, TSubclassOf<class USaveScore> inSub);

protected:



	UFUNCTION(BlueprintCallable, Category = "Events")
		void SaveHighScore(FText inPlayerName, int32 inPoint);

	UPROPERTY(BlueprintReadWrite, Category = "Structure")
		int32 UserIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Structure")
		FString SaveSlotName;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class USaveScore* SaveRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class UUswgRegister* RegisterRef;

	UPROPERTY(BlueprintReadOnly, Category = "Classes")
		TSubclassOf<class USaveScore> SaveScoreBP;
};
