// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgPoint.h"
#include "FlappyBirdPlayerState.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/Engine/Classes/Kismet/KismetStringLibrary.h"

UUswgPoint::UUswgPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgPoint::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(PlStateRef))
	{
		PlStateRef->OnPlayerPointChanged.AddDynamic(this, &UUswgPoint::PlayerPointChanged);
	}
}

void UUswgPoint::PlayerPointChanged(int32 inPoint)
{
	if (IsValid(txtPoint))
	{
		txtPoint->SetText(FText::FromString(UKismetStringLibrary::Conv_IntToString(inPoint)));
	}
}

void UUswgPoint::NativePreConstruct()
{
	Super::NativePreConstruct();
}

TSharedRef<SWidget> UUswgPoint::RebuildWidget()
{
	TSharedRef<SWidget> retWidget = Super::RebuildWidget();
	if (IsValid(szbMain))
	{
		UHorizontalBox* hrz1 = Cast<UHorizontalBox>(szbMain->GetChildAt(0));
		if (IsValid(hrz1))
		{
			UVerticalBox* vrt = Cast<UVerticalBox>(hrz1->GetChildAt(1));
			if (IsValid(vrt))
			{
				UHorizontalBox* hrz2 = Cast<UHorizontalBox>(vrt->GetChildAt(0));
				if (IsValid(hrz2))
				{
					UTextBlock* txtb = Cast<UTextBlock>(hrz2->GetChildAt(1));
					if (IsValid(txtb))
					{
						txtPoint = txtb;
					}
				}
			}
		}
	}
	return retWidget;
}
