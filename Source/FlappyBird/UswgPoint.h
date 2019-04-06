// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UswgParent.h"
#include "UswgPoint.generated.h"

class UTextBlock;

UCLASS()
class FLAPPYBIRD_API UUswgPoint : public UUswgParent
{
	GENERATED_BODY()

public:

	// Consructor
	UUswgPoint(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual TSharedRef<SWidget> RebuildWidget();

protected:

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerPointChanged(int32 inPoint);

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UTextBlock* txtPoint;

};
