// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgMain.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"

UUswgMain::UUswgMain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgMain::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUswgMain::NativePreConstruct()
{
	Super::NativePreConstruct();
}

TSharedRef<SWidget> UUswgMain::RebuildWidget()
{
	TSharedRef<SWidget> retWidget = Super::RebuildWidget();
	if (IsValid(szbMain))
	{
		UHorizontalBox* hrz = Cast<UHorizontalBox>(szbMain->GetChildAt(0));
		if (IsValid(hrz))
		{
			UVerticalBox* vrt = Cast<UVerticalBox>(hrz->GetChildAt(1));
			if (IsValid(vrt))
			{
				UButton* btn1 = Cast<UButton>(vrt->GetChildAt(1));
				if (IsValid(btn1))
				{
					btnRestart = btn1;
					btnRestart->OnClicked.AddDynamic(this, &UUswgMain::RestartClicked);
				}
				UButton* btn2 = Cast<UButton>(vrt->GetChildAt(3));
				if (IsValid(btn2))
				{
					btnHighScore = btn2;
					btnHighScore->OnClicked.AddDynamic(this, &UUswgMain::HighScoreClicked);
				}
				UButton* btn3 = Cast<UButton>(vrt->GetChildAt(5));
				if (IsValid(btn3))
				{
					btnQuit = btn3;
					btnQuit->OnClicked.AddDynamic(this, &UUswgMain::QuitClicked);
				}
			}
		}
	}
	return retWidget;
}

void UUswgMain::RestartClicked()
{
	OnRestartRequested.Broadcast();
}

void UUswgMain::HighScoreClicked()
{
	OnHighScoreRequested.Broadcast();
}

void UUswgMain::QuitClicked()
{
	OnQuitRequested.Broadcast();
}

