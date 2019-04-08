// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine minimal requirement
#include "CoreMinimal.h"

// Base class
#include "Blueprint/UserWidget.h"

// Components
#include "Runtime/UMG/Public/Components/SizeBox.h"

// Generated
#include "UswgParent.generated.h"

class AFlappyBirdCharacter;
class AFlappyBirdPlayerController;
class AFlappyBirdPlayerState;

UCLASS()
class FLAPPYBIRD_API UUswgParent : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Consructor
	UUswgParent(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

protected:
	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdCharacter* CharRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdPlayerState* PlStateRef;
		
	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdPlayerController* PlctRef;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class USizeBox* szbMain;

};

