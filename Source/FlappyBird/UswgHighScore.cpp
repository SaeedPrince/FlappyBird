// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgHighScore.h"
#include "UswgScoreList.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"

UUswgHighScore::UUswgHighScore(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgHighScore::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUswgHighScore::NativePreConstruct()
{
	Super::NativePreConstruct();
}

/*
void UUswgHighScore::ShowHighScore_Implementation(TArray<FText> txtArray, TArray<int32> intArray)
{
	if (IsValid(uScoreList))
	{
		uScoreList->SetScoreList(txtArray, intArray);
		SetVisibility(ESlateVisibility::Visible);
	}
}
*/

void UUswgHighScore::ShowHighScore()
{
	if (IsValid(uScoreList))
	{
		uScoreList->SetScoreList();
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UUswgHighScore::ReturnClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	OnHighScoreReturnToMain.Broadcast();
}

TSharedRef<SWidget> UUswgHighScore::RebuildWidget()
{
	TSharedRef<SWidget> retWidget = Super::RebuildWidget();
	if (IsValid(szbMain))
	{
		UHorizontalBox* hrz0 = Cast<UHorizontalBox>(szbMain->GetChildAt(0));
		if (IsValid(hrz0))
		{
			UVerticalBox* vrt = Cast<UVerticalBox>(hrz0->GetChildAt(1));
			if (IsValid(vrt))
			{
				UUswgScoreList* scrl = Cast<UUswgScoreList>(vrt->GetChildAt(2));
				if (IsValid(scrl))
				{
					uScoreList = scrl;
				}
				UHorizontalBox* hrz1 = Cast<UHorizontalBox>(vrt->GetChildAt(3));
				if (IsValid(hrz1))
				{
					UButton* btn = Cast<UButton>(hrz1->GetChildAt(1));
					if (IsValid(btn))
					{
						btnReturn = btn;
						btnReturn->OnClicked.AddDynamic(this, &UUswgHighScore::ReturnClicked);
					}
				}
			}
		}
	}
	return retWidget;
}

