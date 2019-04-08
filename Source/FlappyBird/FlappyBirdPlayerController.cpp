// Fill out your copyright notice in the Description page of Project Settings.

#include "FlappyBirdPlayerController.h"
#include "FlappyBirdGameMode.h"
#include "FlappyBirdCharacter.h"
#include "FlappyBirdPlayerState.h"
//#include "SaveScore.h"
#include "SaveManager.h"
#include "UswgHighScore.h"
#include "UswgMain.h"
#include "UswgPoint.h"
#include "UswgRegister.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

AFlappyBirdPlayerController::AFlappyBirdPlayerController()
{
	bFirstInput = false;
	JumpSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Jump Sound"));
	JumpSound->SetupAttachment(RootComponent);
	JumpSound->SetAutoActivate(false);
	DeathSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Death Sound"));
	DeathSound->SetupAttachment(RootComponent);
	DeathSound->SetAutoActivate(false);
}

USaveManager* AFlappyBirdPlayerController::GetSaveManager()
{
	return SaveManagerRef;
}

void AFlappyBirdPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CreateAllWidgets();
	USaveManager* svm = NewObject<USaveManager>();
	if (IsValid(svm))
	{
		SaveManagerRef = svm;
		SaveManagerRef->SetReferences(RegisterWidgetRef, SaveScoreBP);
		if (IsValid(PlayerState))
		{
			AFlappyBirdPlayerState* plst = Cast<AFlappyBirdPlayerState>(PlayerState);
			if (IsValid(plst))
			{
				PlStateRef = plst;
				PlStateRef->SetReferences(this, SaveManagerRef);
				PlStateRef->OnHighScoreAchived.AddDynamic(this, &AFlappyBirdPlayerController::HighScoreAchived);
				PlStateRef->OnHighScoreNotAchived.AddDynamic(this, &AFlappyBirdPlayerController::HighScoreNotAchived);
			}
		}
	}
}

void AFlappyBirdPlayerController::HighScoreReturnToMain()
{
	if (IsValid(MainWidgetRef))
	{
		MainWidgetRef->SetVisibility(ESlateVisibility::Visible);
	}
}

void AFlappyBirdPlayerController::PlayerNameRegister(FText inPlayerName, int32 inPoint)
{
	HighScoreRequested();
}

void AFlappyBirdPlayerController::HighScoreAchived(int32 inPoint)
{
	if (IsValid(RegisterWidgetRef))
	{
		if (IsValid(PointWidgetRef))
		{
			PointWidgetRef->SetVisibility(ESlateVisibility::Hidden);
			RegisterWidgetRef->ShowRegister(inPoint);
		}
	}
}

void AFlappyBirdPlayerController::HighScoreNotAchived()
{
	if (IsValid(MainWidgetRef))
	{
		MainWidgetRef->SetVisibility(ESlateVisibility::Visible);
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
	PointWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	if (IsValid(DeathSound))
	{
		DeathSound->Play();
		if (IsValid(CharRef))
		{
			CharRef->Destroy();
			bShowMouseCursor = true;
			bFirstInput = false;
		}
	}
}

void AFlappyBirdPlayerController::RestartRequested()
{
	MainWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	bShowMouseCursor = false;
	OnPlayerRestartedGame.Broadcast();
}

void AFlappyBirdPlayerController::HighScoreRequested()
{
	if (IsValid(MainWidgetRef))
	{
		MainWidgetRef->SetVisibility(ESlateVisibility::Hidden);
		if (IsValid(PointWidgetRef))
		{
			PointWidgetRef->SetVisibility(ESlateVisibility::Hidden);
			if (IsValid(HighScoreWidgetRef))
			{
				HighScoreWidgetRef->ShowHighScore();
			}
		}
	}
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
		PointWidgetRef->SetVisibility(ESlateVisibility::Visible);
	}
	if (IsValid(JumpSound))
	{
		JumpSound->Play();
	}
	OnPlayerPressJump.Broadcast();
}

void AFlappyBirdPlayerController::UnJump()
{
	OnPlayerReleaseJump.Broadcast();
}

void AFlappyBirdPlayerController::CreateAllWidgets()
{
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
					if (IsValid(RegisterWidgetBP))
					{
						UUswgRegister* theRegisterWidgetRef = CreateWidget<UUswgRegister>(this, RegisterWidgetBP);
						if (IsValid(theRegisterWidgetRef))
						{
							RegisterWidgetRef = theRegisterWidgetRef;
							RegisterWidgetRef->AddToViewport(2);
							RegisterWidgetRef->SetVisibility(ESlateVisibility::Hidden);
							RegisterWidgetRef->OnPlayerNameRegister.AddDynamic(this, &AFlappyBirdPlayerController::PlayerNameRegister);
							if (IsValid(HighScoreWidgetBP))
							{
								UUswgHighScore* theHighScoreWidgetRef = CreateWidget<UUswgHighScore>(this, HighScoreWidgetBP);
								if (IsValid(theHighScoreWidgetRef))
								{
									HighScoreWidgetRef = theHighScoreWidgetRef;
									HighScoreWidgetRef->AddToViewport(2);
									HighScoreWidgetRef->SetVisibility(ESlateVisibility::Hidden);
									HighScoreWidgetRef->OnHighScoreReturnToMain.AddDynamic(this, &AFlappyBirdPlayerController::HighScoreReturnToMain);
								}
							}
						}
					}
				}
			}
		}
	}
}
