// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgScoreList.h"
#include "FlappyBirdPlayerController.h"
#include "SaveManager.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Kismet/KismetStringLibrary.h"

UUswgScoreList::UUswgScoreList(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgScoreList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUswgScoreList::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUswgScoreList::SetScoreList()
{
	if (IsValid(PlctRef))
	{
		USaveManager* svm = PlctRef->GetSaveManager();
		if (IsValid(svm))
		{
			TArray<FText> txtArray;
			TArray<int32> intArray;
			svm->LoadHighScore(txtArray, intArray);
			for (int i = 0; i < txtArray.Num(); i++)
			{
				if (IsValid(txtNames[i]))
				{
					txtNames[i]->SetText(txtArray[i]);
				}
				if (IsValid(txtScores[i]))
				{
					txtScores[i]->SetText(FText::FromString(UKismetStringLibrary::Conv_IntToString(intArray[i])));
				}
			}
		}
	}

}

TSharedRef<SWidget> UUswgScoreList::RebuildWidget()
{
	TSharedRef<SWidget> retWidget = Super::RebuildWidget();
	txtNames.Empty();
	txtScores.Empty();
	if (IsValid(szbMain))
	{
		UHorizontalBox* hrz = Cast<UHorizontalBox>(szbMain->GetChildAt(0));
		if (IsValid(hrz))
		{
			UVerticalBox* vrt0 = Cast<UVerticalBox>(hrz->GetChildAt(1));
			if (IsValid(vrt0))
			{
				for (int i = 0; i < 10; i++)
				{
					UTextBlock* txtb = Cast<UTextBlock>(vrt0->GetChildAt(i));
					if (IsValid(txtb))
					{
						txtNames.Add(txtb);
					}
				}
			}
			UVerticalBox* vrt1 = Cast<UVerticalBox>(hrz->GetChildAt(3));
			if (IsValid(vrt1))
			{
				for (int i = 0; i < 10; i++)
				{
					UTextBlock* txtc = Cast<UTextBlock>(vrt1->GetChildAt(i));
					if (IsValid(txtc))
					{
						txtScores.Add(txtc);
					}
				}
			}
		}
	}
	return retWidget;
}
