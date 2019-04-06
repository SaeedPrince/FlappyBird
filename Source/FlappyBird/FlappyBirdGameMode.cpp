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
	bDebug = false;
	BarrierFrequency = 3.0f;
	BarrierXOffset = 1800.0f;
	BarrierZMin = 800;
	BarrierZMax = 1000;
	CharacterSpawnLocation = FVector(-312.0f, -13.0f, 910.0f);
	BarrierFirstSpawnLocation = FVector(1500.0f, -13.0f, 910.0f);
	BarrierSpawnLocation = BarrierFirstSpawnLocation;
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

float AFlappyBirdGameMode::GetBarrierFrequency()
{
	return BarrierFrequency;
}

void AFlappyBirdGameMode::StartGame()
{
	if (IsValid(CharacterBP))
	{
		AFlappyBirdCharacter* SpawnedCharacter = Cast<AFlappyBirdCharacter>(SpawnFlabbyBirdActor(CharacterBP, CharacterSpawnLocation));
		if (IsValid(SpawnedCharacter))
		{
			CharRef = SpawnedCharacter;
			CharRef->OnCharacterGoesToLeftBoundary.AddDynamic(this, &AFlappyBirdGameMode::CharacterGoesToLeftBoundary);
			CharRef->OnCharacterCrashed.AddDynamic(this, &AFlappyBirdGameMode::CharacterCrashed);
			CtrlRef->Possess(CharRef);
		}
	}
}

void AFlappyBirdGameMode::CharacterCrashed()
{
	PrintOnScreen("CharacterCrashed");
	GetWorld()->GetTimerManager().ClearTimer(TimerBarrier);
	TimerBarrier.Invalidate();
	BarrierSpawnLocation = BarrierFirstSpawnLocation;
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
	if (IsValid(BarrierBP) && IsValid(CharRef))
	{
		int32 zBar = UKismetMathLibrary::RandomIntegerInRange(BarrierZMin, BarrierZMax);
		BarrierZLocation = UKismetMathLibrary::Conv_IntToFloat(zBar);
		BarrierSpawnLocation.Z = BarrierZLocation;
		ABarrierPaperSpriteActor* SpawnedBarrier = Cast<ABarrierPaperSpriteActor>(SpawnFlabbyBirdActor(BarrierBP, BarrierSpawnLocation));
		if (IsValid(SpawnedBarrier))
		{
			BarrierSpawnLocation = FVector(BarrierSpawnLocation.X + BarrierXOffset, BarrierSpawnLocation.Y, BarrierSpawnLocation.Z);
		}
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