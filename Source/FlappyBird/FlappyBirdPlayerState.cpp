// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdPlayerState.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AFlappyBirdPlayerState::AFlappyBirdPlayerState()
{
	PlayerPoint = 0;
	StartDelay = 0.0f;
}

void AFlappyBirdPlayerState::BeginPlay()
{
	Super::BeginPlay();
	AFlappyBirdPlayerController* cntr = Cast<AFlappyBirdPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(cntr))
	{
		CtrlRef = cntr;
		CtrlRef->OnPlayerStartedInput.AddDynamic(this, &AFlappyBirdPlayerState::PlayerStartedInput);
	}
	AFlappyBirdGameMode* gmme = Cast<AFlappyBirdGameMode>(GetWorld()->GetAuthGameMode());
	if (IsValid(gmme))
	{
		GameModeRef = gmme;
	}
}

void AFlappyBirdPlayerState::PlayerStartedInput()
{
	GetWorld()->GetTimerManager().SetTimer(TimerDelay, this, &AFlappyBirdPlayerState::FirstDelay, StartDelay);
	PlayerPoint = 0;
	OnPlayerPointChanged.Broadcast(PlayerPoint);
}

void AFlappyBirdPlayerState::FirstDelay()
{
	if (IsValid(GameModeRef))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerPoint, this, &AFlappyBirdPlayerState::CountPoint, GameModeRef->GetBarrierFrequency(), true);
	}
}

void AFlappyBirdPlayerState::CountPoint()
{
	PlayerPoint++;
	OnPlayerPointChanged.Broadcast(PlayerPoint);
}



