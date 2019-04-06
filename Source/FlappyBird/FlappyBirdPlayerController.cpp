// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdPlayerController.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdCharacter.h"
#include "FlappyBirdPlayerState.h"
#include "UswgMain.h"
#include "UswgPoint.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

AFlappyBirdPlayerController::AFlappyBirdPlayerController()
{
	bFirstInput = false;
}

void AFlappyBirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(MainWidgetBP))
	{
		UUswgMain* theMainWidgetRef = CreateWidget<UUswgMain>(this, MainWidgetBP);
		if (IsValid(theMainWidgetRef))
		{
			MainWidgetRef = theMainWidgetRef;
			MainWidgetRef->AddToViewport(2);
			MainWidgetRef->SetVisibility(ESlateVisibility::Hidden);
			MainWidgetRef->OnRestartRequested.AddDynamic(this, &AFlappyBirdPlayerController::RestartRequested);
			MainWidgetRef->OnHighScoreRequested.AddDynamic(this, &AFlappyBirdPlayerController::HighScoreRequested);
			MainWidgetRef->OnQuitRequested.AddDynamic(this, &AFlappyBirdPlayerController::QuitRequested);
			if (IsValid(PointWidgetBP))
			{
				UUswgPoint* thePointWidgetRef = CreateWidget<UUswgPoint>(this, PointWidgetBP);
				if (IsValid(thePointWidgetRef))
				{
					PointWidgetRef = thePointWidgetRef;
					PointWidgetRef->AddToViewport(1);
				}
			}
		}
	}
}

void AFlappyBirdPlayerController::SetCharacterRef(AFlappyBirdCharacter* theRef)
{
	if (IsValid(theRef))
	{
		CharRef = theRef;
		CharRef->OnCharacterCrashed.AddDynamic(this, &AFlappyBirdPlayerController::CharacterCrashed);
	}
}

void AFlappyBirdPlayerController::CharacterCrashed()
{
	CharRef->Destroy();
	bShowMouseCursor = true;
	MainWidgetRef->SetVisibility(ESlateVisibility::Visible);
	bFirstInput = false;
}

void AFlappyBirdPlayerController::RestartRequested()
{
	MainWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	bShowMouseCursor = false;
	OnPlayerRestartedGame.Broadcast();
}

void AFlappyBirdPlayerController::HighScoreRequested()
{

}

void AFlappyBirdPlayerController::QuitRequested()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
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

