// Fill out your copyright notice in the Description page of Project Settings.

#include "UswgParent.h"
#include "FlappyBirdCharacter.h"
#include "FlappyBirdPlayerController.h"
#include "FlappyBirdPlayerState.h"

UUswgParent::UUswgParent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UUswgParent::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUswgParent::NativePreConstruct()
{
	Super::NativePreConstruct();
}

TSharedRef<SWidget> UUswgParent::RebuildWidget()
{
	TSharedRef<SWidget> retWidget = Super::RebuildWidget();
	APlayerController* parentController = GetOwningPlayer();
	if (IsValid(parentController))
	{
		AFlappyBirdPlayerController* cntr = Cast<AFlappyBirdPlayerController>(parentController);
		if (IsValid(cntr))
		{
			PlctRef = cntr;
			AFlappyBirdPlayerState* plst = Cast<AFlappyBirdPlayerState>(PlctRef->PlayerState);
			if (IsValid(plst))
			{
				PlStateRef = plst;
			}
		}
	}
	UPanelWidget* uwg = Cast<UPanelWidget>(GetRootWidget());
	if (IsValid(uwg))
	{
		szbMain = Cast<USizeBox>(uwg);
	}
	return retWidget;
}
