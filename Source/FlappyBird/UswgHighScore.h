// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UswgParent.h"
#include "UswgHighScore.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHighScoreReturnToMain);

class UButton;
class UUswgScoreList;

UCLASS()
class FLAPPYBIRD_API UUswgHighScore : public UUswgParent
{
	GENERATED_BODY()
	
public:

	// Consructor
	UUswgHighScore(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void ShowHighScore();

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "High Score")
		FHighScoreReturnToMain OnHighScoreReturnToMain;

protected:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void ReturnClicked();

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UButton* btnReturn;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UUswgScoreList* uScoreList;

};