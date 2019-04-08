// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdPlayerState.h"
#include "FlappyBirdCharacter.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdPlayerController.h"
#include "SaveManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


AFlappyBirdPlayerState::AFlappyBirdPlayerState()
{
	PlayerPoint = 0;
}

void AFlappyBirdPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AFlappyBirdPlayerState::SetReferences(AFlappyBirdPlayerController* theRef, USaveManager* inSaveRef)
{
	if (IsValid(theRef))
	{
		CtrlRef = theRef;
		CtrlRef->OnPlayerStartedInput.AddDynamic(this, &AFlappyBirdPlayerState::PlayerStartedInput);
		if (IsValid(inSaveRef))
		{
			SaveRef = inSaveRef;
		}
	}
}

void AFlappyBirdPlayerState::PlayerStartedInput()
{
	PlayerPoint = 0;
	OnPlayerPointChanged.Broadcast(PlayerPoint);
	if (IsValid(CtrlRef))
	{
		AFlappyBirdCharacter* chrc = Cast<AFlappyBirdCharacter>(CtrlRef->GetPawn());
		if (IsValid(chrc))
		{
			CharRef = chrc;
			CharRef->OnCharacterPassed.AddDynamic(this, &AFlappyBirdPlayerState::CharacterPassed);
			CharRef->OnCharacterCrashed.AddDynamic(this, &AFlappyBirdPlayerState::CharacterCrashed);
		}
	}
}

void AFlappyBirdPlayerState::CharacterCrashed()
{
	if (IsValid(SaveRef))
	{
		if (SaveRef->CanAchieveHighScore(PlayerPoint))
		{
			OnHighScoreAchived.Broadcast(PlayerPoint);
		}
		else
		{
			OnHighScoreNotAchived.Broadcast();
		}
	}
}

void AFlappyBirdPlayerState::CharacterPassed()
{
	PlayerPoint++;
	OnPlayerPointChanged.Broadcast(PlayerPoint);
}