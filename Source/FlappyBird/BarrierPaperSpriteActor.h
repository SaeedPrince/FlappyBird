// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "BarrierPaperSpriteActor.generated.h"

class UPaperSpriteComponent;

UCLASS()
class FLAPPYBIRD_API ABarrierPaperSpriteActor : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	ABarrierPaperSpriteActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* TopRenderComponent;

	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Sprite,Rendering,Physics,Components|Sprite", AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* DownRenderComponent;
};
