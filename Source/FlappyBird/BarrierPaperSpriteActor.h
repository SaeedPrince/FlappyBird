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

	//virtual void OnConstruction(const FTransform& transform) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Events")
		void DestroyMe();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float DestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		FTimerHandle TimerDestroy;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UFlappyBirdPaperSpriteComponent* TopSprite;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
		class UFlappyBirdPaperSpriteComponent* DownSprite;

};
