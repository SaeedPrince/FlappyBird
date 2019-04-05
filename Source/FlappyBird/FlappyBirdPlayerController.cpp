// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdPlayerController.h"

AFlappyBirdPlayerController::AFlappyBirdPlayerController()
{
	bFirstInput = false;

}

void AFlappyBirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*
	if (IsValid(MainWidgetBP))
	{
		theWidgetRef = CreateWidget<UUswgMain>(this, MainWidgetBP);
		if (IsValid(theWidgetRef))
		{
			MainWidgetRef = theWidgetRef;
			MainWidgetRef->AddToViewport(1);
			MainWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	*/
}

void AFlappyBirdPlayerController::SetupInputComponent()
{

	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Touch handle
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFlappyBirdPlayerController::FingerTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AFlappyBirdPlayerController::FingerTouchReleased);

	// Action mapping
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFlappyBirdPlayerController::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFlappyBirdPlayerController::StopJump);
}

void AFlappyBirdPlayerController::FingerTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();
}

void AFlappyBirdPlayerController::FingerTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	UnJump();
}

void AFlappyBirdPlayerController::StartJump()
{
	Jump();
}

void AFlappyBirdPlayerController::StopJump()
{
	UnJump();
}

void AFlappyBirdPlayerController::Jump()
{
	if (!bFirstInput)
	{
		bFirstInput = true;
		OnPlayerStartedInput.Broadcast();
	}
	OnPlayerPressJump.Broadcast();
}

void AFlappyBirdPlayerController::UnJump()
{
	OnPlayerReleaseJump.Broadcast();
}

