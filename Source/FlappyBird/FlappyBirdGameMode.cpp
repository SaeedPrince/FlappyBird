// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FlappyBirdGameMode.h"
#include "FlappyBirdCharacter.h"
#include "BarrierPaperSpriteActor.h"
#include "FlappyBirdPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AFlappyBirdGameMode::AFlappyBirdGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AFlappyBirdCharacter::StaticClass();
	bDebug = false;
	BarrierFrequency = 3.0f;
	BarrierXOffset = 800.0f;
	BarrierSpawnLocation = FVector(-312.0f, -13.0f, 910.0f);

}

void AFlappyBirdGameMode::BeginPlay()
{
	Super::BeginPlay();
	AFlappyBirdPlayerController* cntr = Cast<AFlappyBirdPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(cntr))
	{
		CtrlRef = cntr;
		CtrlRef->OnPlayerStartedInput.AddDynamic(this, &AFlappyBirdGameMode::PlayerStartedInput);
	}

	AFlappyBirdCharacter* chrt = Cast<AFlappyBirdCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(chrt))
	{
		CharRef = chrt;
		CharRef->OnCharacterGoesToLeftBoundary.AddDynamic(this, &AFlappyBirdGameMode::CharacterGoesToLeftBoundary);
	}

}

void AFlappyBirdGameMode::CharacterGoesToLeftBoundary(float inLeftBoundary)
{
	BarrierSpawnLocation = FVector(inLeftBoundary + BarrierXOffset, BarrierSpawnLocation.Y, BarrierSpawnLocation.Z);
}

void AFlappyBirdGameMode::PlayerStartedInput()
{
	GetWorld()->GetTimerManager().SetTimer(TimerBarrier, this, &AFlappyBirdGameMode::BarrierManager, BarrierFrequency, true);
}

void AFlappyBirdGameMode::BarrierManager()
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(BarrierSpawnLocation);
	SpawnTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (IsValid(BarrierBP))
	{
		ABarrierPaperSpriteActor* SpawnedBarrier = GetWorld()->SpawnActor<ABarrierPaperSpriteActor>(BarrierBP, SpawnTransform, SpawnParameters);
		if (IsValid(SpawnedBarrier))
		{
			BarrierSpawnLocation = FVector(BarrierSpawnLocation.X + BarrierXOffset, BarrierSpawnLocation.Y, BarrierSpawnLocation.Z);
			//Barriers.Add(SpawnedBarrier);
		}
	}


}