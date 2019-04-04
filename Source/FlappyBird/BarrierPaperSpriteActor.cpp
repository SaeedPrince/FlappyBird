// Fill out your copyright notice in the Description page of Project Settings.

#include "BarrierPaperSpriteActor.h"
//#include "/Installs/UE_4.21/Engine/Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "Engine/CollisionProfile.h"
#include "PaperSpriteComponent.h"

ABarrierPaperSpriteActor::ABarrierPaperSpriteActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TopRenderComponent = GetRenderComponent();
	DownRenderComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DownRenderComponent"));
	DownRenderComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	DownRenderComponent->Mobility = EComponentMobility::Static;

	RootComponent = TopRenderComponent;
}
