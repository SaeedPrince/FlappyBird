// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FlappyBirdPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHighScoreNotAchived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerPointChanged, int32, inPoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHighScoreAchived, int32, inPoint);

class AFlappyBirdCharacter;
class AFlappyBirdGameMode;
class AFlappyBirdPlayerController;
class USaveManager;

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AFlappyBirdPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Setters")
		void SetReferences(class AFlappyBirdPlayerController* theRef, class USaveManager* inSaveRef);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Point")
		FPlayerPointChanged OnPlayerPointChanged;

	UPROPERTY(BlueprintAssignable, Category = "Point")
		FHighScoreAchived OnHighScoreAchived;

	UPROPERTY(BlueprintAssignable, Category = "Point")
		FHighScoreNotAchived OnHighScoreNotAchived;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Events")
		void CharacterCrashed();
		
	UFUNCTION(BlueprintCallable, Category = "Events")
		void CharacterPassed();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerStartedInput();

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 PlayerPoint;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class AFlappyBirdPlayerController* CtrlRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class AFlappyBirdCharacter* CharRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class USaveManager* SaveRef;

};
