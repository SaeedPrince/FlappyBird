// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UswgParent.h"
#include "UswgMain.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartRequested);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHighScoreRequested);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuitRequested);

class UButton;

UCLASS()
class FLAPPYBIRD_API UUswgMain : public UUswgParent
{
	GENERATED_BODY()

public:

	// Consructor
	UUswgMain(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Menu")
		FRestartRequested OnRestartRequested;

	UPROPERTY(BlueprintAssignable, Category = "Menu")
		FHighScoreRequested OnHighScoreRequested;

	UPROPERTY(BlueprintAssignable, Category = "Menu")
		FQuitRequested OnQuitRequested;

protected:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void RestartClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void HighScoreClicked();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void QuitClicked();

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UButton* btnRestart;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UButton* btnHighScore;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UButton* btnQuit;

};
