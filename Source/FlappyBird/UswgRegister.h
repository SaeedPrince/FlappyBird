// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UswgParent.h"
#include "UswgRegister.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayerNameRegister, FText, inPlayerName, int32, inPoint);

class UButton;
class UEditableTextBox;
class UTextBlock;

UCLASS()
class FLAPPYBIRD_API UUswgRegister : public UUswgParent
{
	GENERATED_BODY()
	
public:

	// Consructor
	UUswgRegister(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void ShowRegister(int32 inScore);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Register")
		FPlayerNameRegister OnPlayerNameRegister;

protected:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void EnterClicked();

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		int32 PlayerScore;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UButton* btnEnter;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UEditableTextBox* txtName;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UTextBlock* txtPoint;

};


