// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgRegister.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/Engine/Classes/Kismet/KismetStringLibrary.h"

UUswgRegister::UUswgRegister(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgRegister::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUswgRegister::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUswgRegister::ShowRegister(int32 inScore)
{
	PlayerScore = inScore;
	FString str1 = FString("Your Score: ");
	FString str2 = UKismetStringLibrary::Conv_IntToString(inScore);
	if (IsValid(txtPoint))
	{
		txtPoint->SetText(FText::FromString(UKismetStringLibrary::Concat_StrStr(str1, str2)));
		if (IsValid(txtName))
		{
			txtName->SetText(FText::FromString(""));
			txtName->SetKeyboardFocus();
			SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UUswgRegister::EnterClicked()
{
	if (IsValid(txtName))
	{
		OnPlayerNameRegister.Broadcast(txtName->GetText(), PlayerScore);
	}
	SetVisibility(ESlateVisibility::Hidden);
}

TSharedRef<SWidget> UUswgRegister::RebuildWidget()
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
				UTextBlock* txtb = Cast<UTextBlock>(vrt->GetChildAt(2));
				if (IsValid(txtb))
				{
					txtPoint = txtb;
				}
				UHorizontalBox* hrz1 = Cast<UHorizontalBox>(vrt->GetChildAt(3));
				if (IsValid(hrz1))
				{
					UEditableTextBox* edtt = Cast<UEditableTextBox>(hrz1->GetChildAt(1));
					if (IsValid(edtt))
					{
						txtName = edtt;
					}
				}
				UHorizontalBox* hrz2 = Cast<UHorizontalBox>(vrt->GetChildAt(5));
				if (IsValid(hrz2))
				{
					UButton* btn = Cast<UButton>(hrz2->GetChildAt(1));
					if (IsValid(btn))
					{
						btnEnter = btn;
						btnEnter->OnClicked.AddDynamic(this, &UUswgRegister::EnterClicked);
					}
				}
			}
		}
	}
	return retWidget;
}