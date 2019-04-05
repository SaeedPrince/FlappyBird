// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlappyBirdPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerStartedInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerPressJump);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerReleaseJump);

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Constructors
	AFlappyBirdPlayerController();

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerStartedInput OnPlayerStartedInput;

	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerPressJump OnPlayerPressJump;

	UPROPERTY(BlueprintAssignable, Category = "Input")
		FPlayerReleaseJump OnPlayerReleaseJump;

protected:

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	//virtual void PlayerTick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

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

	UPROPERTY(BlueprintReadWrite, Category = "Flags")
		bool bFirstInput;

	/*
	UPROPERTY(BlueprintReadWrite, Category = "Widgets")
		class UUswgMain* MainWidgetRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<class UUswgMain> MainWidgetBP;
	*/

};
