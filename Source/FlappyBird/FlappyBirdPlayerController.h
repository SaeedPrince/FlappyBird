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
class AFlappyBirdPlayerState;
class USaveManager;
class UUswgHighScore;
class UUswgMain;
class UUswgPoint;
class UUswgRegister;

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Constructors
	AFlappyBirdPlayerController();

	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Getters")
		class USaveManager* GetSaveManager();
	
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
	
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Widgets")
		void CreateAllWidgets();

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
		
	UFUNCTION(BlueprintCallable, Category = "Player State")
		void HighScoreAchived(int32 inPoint);

	UFUNCTION(BlueprintCallable, Category = "Player State")
		void HighScoreNotAchived();

	UFUNCTION(BlueprintCallable, Category = "Register")
		void PlayerNameRegister(FText inPlayerName, int32 inPoint);

	UFUNCTION(BlueprintCallable, Category = "High Score")
		void HighScoreReturnToMain();

	UFUNCTION(BlueprintCallable, Category = "Character")
		void CharacterCrashed();
		
	// Properties
	UPROPERTY(BlueprintReadWrite, Category = "Flags")
		bool bFirstInput;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects|Other")
		class AFlappyBirdCharacter* CharRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects|Other")
		class AFlappyBirdPlayerState* PlStateRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAudioComponent* JumpSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAudioComponent* DeathSound;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects|Other")
		class USaveManager* SaveManagerRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects|Widgets")
		class UUswgHighScore* HighScoreWidgetRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects|Widgets")
		class UUswgMain* MainWidgetRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects|Widgets")
		class UUswgPoint* PointWidgetRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects|Widgets")
		class UUswgRegister* RegisterWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes|Other")
		TSubclassOf<class USaveScore> SaveScoreBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes|Widgets")
		TSubclassOf<class UUswgHighScore> HighScoreWidgetBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes|Widgets")
		TSubclassOf<class UUswgMain> MainWidgetBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes|Widgets")
		TSubclassOf<class UUswgPoint> PointWidgetBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes|Widgets")
		TSubclassOf<class UUswgRegister> RegisterWidgetBP;

};
