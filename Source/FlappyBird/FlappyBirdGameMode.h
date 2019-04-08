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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		FVector GetBirdSpawnLocation();

protected:

	virtual void BeginPlay() override;

	// Functions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Spawn")
		AActor* SpawnFlabbyBirdActor(TSubclassOf<AActor> ActorBP, const FVector& SpawnLocation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Events")
		void PrintOnScreen(const FString& inString, bool bScreen = true, bool bLog = true, const FLinearColor& inColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), float inDuration = 8.0f);

	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerStartedInput();
		
	UFUNCTION(BlueprintCallable, Category = "Events")
		void BarrierManager();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void StartGame();
		
	// Properties
	UPROPERTY(BlueprintReadWrite, Category = "Barrier")
		int32 BarrierCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		int32 BarrierMaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		int32 BarrierZMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		int32 BarrierZMax;

	UPROPERTY(BlueprintReadOnly, Category = "Barrier")
		float BarrierZLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		float BarrierFrequency;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		float BarrierXOffset;

	UPROPERTY(BlueprintReadWrite, Category = "Timers")
		FTimerHandle TimerBarrier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Barrier")
		float BarrierFirstXOffset;

	UPROPERTY(BlueprintReadWrite, Category = "Barrier")
		FVector BarrierSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		FVector CharacterSpawnLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdCharacter* CharRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdPlayerController* CtrlRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Classes")
		TSubclassOf<class ABarrierPaperSpriteActor> BarrierBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Classes")
		TSubclassOf<class AFlappyBirdCharacter> CharacterBP;

};
