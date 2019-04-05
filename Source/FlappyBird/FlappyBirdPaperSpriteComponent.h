// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "FlappyBirdPaperSpriteComponent.generated.h"

/**
 * 
 */
UCLASS(ShowCategories = (Mobility, Transform), ClassGroup = Paper2D, meta = (BlueprintSpawnableComponent))
class FLAPPYBIRD_API UFlappyBirdPaperSpriteComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
	
public:

	// Constructor
	UFlappyBirdPaperSpriteComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
