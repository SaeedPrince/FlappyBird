// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyBirdPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerRestartedGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerStartedInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerPressJump);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerReleaseJump);

class AFlappyBirdCharacter;
class UUswgMain;
class UUswgPoint;

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Constructors
	AFlappyBirdPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Setters")
		void SetCharacterRef(class AFlappyBirdCharacter* theRef);

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerStartedInput OnPlayerStartedInput;

	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerPressJump OnPlayerPressJump;

	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerReleaseJump OnPlayerReleaseJump;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FPlayerRestartedGame OnPlayerRestartedGame;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void PlayerTick(float DeltaTime) override;
	
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
		void FingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void FingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void StopJump();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Jump();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void UnJump();

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void RestartRequested();

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void HighScoreRequested();

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void QuitRequested();
		
	UFUNCTION(BlueprintCallable, Category = "Character")
		void CharacterCrashed();
		
	// Properties
	UPROPERTY(BlueprintReadWrite, Category = "Flags")
		bool bFirstInput;

	/*
	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdGameMode* GameModeRef;
	*/

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdCharacter* CharRef;
		
	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
		class UUswgMain* MainWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<class UUswgMain> MainWidgetBP;

	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
		class UUswgPoint* PointWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<class UUswgPoint> PointWidgetBP;

};
