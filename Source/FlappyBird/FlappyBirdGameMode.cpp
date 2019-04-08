// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FlappyBirdGameMode.h"
#include "FlappyBirdCharacter.h"
#include "BarrierPaperSpriteActor.h"
#include "FlappyBirdPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

AFlappyBirdGameMode::AFlappyBirdGameMode()
{
	// Set default pawn class to our character
	BarrierCount = 0;
	BarrierMaxCount = 20;
	BarrierZMin = 800;
	BarrierZMax = 1000;
	BarrierFrequency = 0.5f;
	BarrierXOffset = 1800.0f;
	BarrierFirstXOffset = BarrierXOffset * 2.0f;
	CharacterSpawnLocation = FVector(-312.0f, -13.0f, 910.0f);
	//BarrierFirstSpawnLocation = FVector(1500.0f, -13.0f, 910.0f);
}

void AFlappyBirdGameMode::BeginPlay()
{
	Super::BeginPlay();
	AFlappyBirdPlayerController* cntr = Cast<AFlappyBirdPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(cntr))
	{
		CtrlRef = cntr;
		CtrlRef->OnPlayerStartedInput.AddDynamic(this, &AFlappyBirdGameMode::PlayerStartedInput);
		CtrlRef->OnPlayerRestartedGame.AddDynamic(this, &AFlappyBirdGameMode::StartGame);
		StartGame();
	}
}

FVector AFlappyBirdGameMode::GetBirdSpawnLocation()
{
	return CharacterSpawnLocation;
}

void AFlappyBirdGameMode::StartGame()
{
	if (IsValid(CharacterBP))
	{
		AFlappyBirdCharacter* SpawnedCharacter = Cast<AFlappyBirdCharacter>(SpawnFlabbyBirdActor(CharacterBP, CharacterSpawnLocation));
		if (IsValid(SpawnedCharacter))
		{
			CharRef = SpawnedCharacter;
			CtrlRef->Possess(CharRef);
		}
	}
}

void AFlappyBirdGameMode::PlayerStartedInput()
{
	if (IsValid(CharRef))
	{
		FVector theLoc = CharRef->GetActorLocation();
		BarrierSpawnLocation = FVector(theLoc.X + BarrierFirstXOffset, theLoc.Y, theLoc.Z);
		if (BarrierCount < BarrierMaxCount)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerBarrier, this, &AFlappyBirdGameMode::BarrierManager, BarrierFrequency, true);
		}
	}
}

void AFlappyBirdGameMode::BarrierManager()
{
	if (BarrierCount < BarrierMaxCount)
	{
		if (IsValid(BarrierBP))
		{
			int32 zBar = UKismetMathLibrary::RandomIntegerInRange(BarrierZMin, BarrierZMax);
			BarrierZLocation = UKismetMathLibrary::Conv_IntToFloat(zBar);
			BarrierSpawnLocation.Z = BarrierZLocation;
			ABarrierPaperSpriteActor* SpawnedBarrier = Cast<ABarrierPaperSpriteActor>(SpawnFlabbyBirdActor(BarrierBP, BarrierSpawnLocation));
			if (IsValid(SpawnedBarrier))
			{
				BarrierSpawnLocation = FVector(BarrierSpawnLocation.X + BarrierXOffset, BarrierSpawnLocation.Y, BarrierSpawnLocation.Z);
				BarrierCount++;
			}
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerBarrier);
		TimerBarrier.Invalidate();
	}
}

AActor* AFlappyBirdGameMode::SpawnFlabbyBirdActor_Implementation(TSubclassOf<AActor> ActorBP, const FVector& SpawnLocation)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorBP, SpawnTransform, SpawnParameters);
	return SpawnedActor;
}