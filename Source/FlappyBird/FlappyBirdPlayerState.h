// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FlappyBirdPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerPointChanged, int32, inPoint);

class AFlappyBirdGameMode;
class AFlappyBirdPlayerController;

UCLASS()
class FLAPPYBIRD_API AFlappyBirdPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AFlappyBirdPlayerState();

	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Point")
		FPlayerPointChanged OnPlayerPointChanged;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Events")
		void CountPoint();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void FirstDelay();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerStartedInput();

	UPROPERTY(BlueprintReadWrite, Category = "Variables")
		int32 PlayerPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coordination")
		float StartDelay;

	UPROPERTY(BlueprintReadWrite, Category = "Timers")
		FTimerHandle TimerDelay;
		
	UPROPERTY(BlueprintReadWrite, Category = "Timers")
		FTimerHandle TimerPoint;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class AFlappyBirdGameMode* GameModeRef;

	UPROPERTY(BlueprintReadWrite, Category = "Game Objects")
		class AFlappyBirdPlayerController* CtrlRef;

};
