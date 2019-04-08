// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "BarrierPaperSpriteActor.generated.h"

UCLASS()
class FLAPPYBIRD_API ABarrierPaperSpriteActor : public AActor
{
	GENERATED_BODY()

public:

	ABarrierPaperSpriteActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:

	virtual void BeginPlay() override;


};
