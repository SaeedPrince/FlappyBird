// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrierPaperSpriteActor.h"
#include "FlappyBirdPaperSpriteComponent.h"

ABarrierPaperSpriteActor::ABarrierPaperSpriteActor(const FObjectInitializer& ObjectInitializer)	: Super(ObjectInitializer)
{
	DestroyTime = 4.0f;
}

/*
void ABarrierPaperSpriteActor::OnConstruction(const FTransform& transform)
{
	if (IsValid(RootComponent))
	{
		TArray <USceneComponent*> childComps;
		RootComponent->GetChildrenComponents(false, childComps);
		if (IsValid(childComps[0]))
		{
			UFlappyBirdPaperSpriteComponent* tSprite = Cast<UFlappyBirdPaperSpriteComponent>(childComps[0]);
			if (IsValid(tSprite))
			{
				TopSprite = tSprite;
				TopSprite->OnComponentBeginOverlap.AddDynamic(this, &ABarrierPaperSpriteActor::CollisionOverlapStart);
			}
			UFlappyBirdPaperSpriteComponent* dSprite = Cast<UFlappyBirdPaperSpriteComponent>(childComps[1]);
			if (IsValid(dSprite))
			{
				DownSprite = dSprite;
				TopSprite->OnComponentBeginOverlap.AddDynamic(this, &ABarrierPaperSpriteActor::CollisionOverlapStart);
			}
		}
	}
}
*/

// Begin Play
void ABarrierPaperSpriteActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerDestroy, this, &ABarrierPaperSpriteActor::DestroyMe, DestroyTime);
}

void ABarrierPaperSpriteActor::DestroyMe()
{
	Destroy();
}

/*
void ABarrierPaperSpriteActor::CollisionOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
*/
