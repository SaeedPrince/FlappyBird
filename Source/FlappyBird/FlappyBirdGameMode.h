// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameMode.generated.h"

class AFlappyBirdCharacter;
class AFlappyBirdPlayerController;

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of FlappyBirdCharacter
 */

UCLASS(BlueprintType)
class AFlappyBirdGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFlappyBirdGameMode();


protected:

	virtual void BeginPlay() override;

	// Functions
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Events")
		void PrintOnScreen(const FString& inString, bool bScreen = true, bool bLog = true, const FLinearColor& inColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), float inDuration = 8.0f);

	UFUNCTION(BlueprintCallable, Category = "Events")
		void CharacterGoesToLeftBoundary(float inLeftBoundary);
		
	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerStartedInput();
		
	UFUNCTION(BlueprintCallable, Category = "Events")
		void BarrierManager();

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Mode")
		bool bDebug;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		float BarrierFrequency;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		float BarrierXOffset;

	UPROPERTY(BlueprintReadWrite, Category = "Timers")
		FTimerHandle TimerBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barrier")
		FVector BarrierSpawnLocation;
	
	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdCharacter* CharRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdPlayerController* CtrlRef;

	/*
	UPROPERTY(BlueprintReadOnly, Category = "Barrier")
		TArray<class ABarrierPaperSpriteActor*> Barriers;
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Classes")
		TSubclassOf<class ABarrierPaperSpriteActor> BarrierBP;

};
