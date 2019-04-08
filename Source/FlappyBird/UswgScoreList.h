// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UswgParent.h"
#include "UswgScoreList.generated.h"

UCLASS()
class FLAPPYBIRD_API UUswgScoreList : public UUswgParent
{
	GENERATED_BODY()

public:

	// Consructor
	UUswgScoreList(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void SetScoreList();

protected:

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TArray<class UTextBlock*> txtNames;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		TArray<class UTextBlock*> txtScores;
};