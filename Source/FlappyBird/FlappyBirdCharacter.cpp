// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FlappyBirdCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "BarrierPaperSpriteActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "FlappyBirdPlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// AFlappyBirdCharacter

AFlappyBirdCharacter::AFlappyBirdCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	MovementAmount = 1.0f;
	MovementFrequency = 0.01f;

	BoundaryLeftX = -3000.0f;
	BoundaryRightX = 3000.0f;

	// Set the size of our collision capsule.
	theCapsule = GetCapsuleComponent();
	theCapsule->SetCapsuleHalfHeight(96.0f);
	theCapsule->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	ChMovement = GetCharacterMovement();
	if (IsValid(ChMovement))
	{
		ChMovement->bOrientRotationToMovement = false;

		// Configure character movement
		ChMovement->GravityScale = 0.0f;
		ChMovement->AirControl = 0.80f;
		ChMovement->JumpZVelocity = 1000.f;
		ChMovement->GroundFriction = 3.0f;
		ChMovement->MaxWalkSpeed = 600.0f;
		ChMovement->MaxFlySpeed = 600.0f;

		// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
		ChMovement->bConstrainToPlane = true;
		ChMovement->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

		// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
		// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
		// behavior on the edge of a ledge versus inclines by setting this to true or false
		GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	}

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

//////////////////////////////////////////////////////////////////////////
// Animation

void AFlappyBirdCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AFlappyBirdCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	
}


//////////////////////////////////////////////////////////////////////////
// Input

/*
void AFlappyBirdCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFlappyBirdCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFlappyBirdCharacter::StopJump);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AFlappyBirdCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFlappyBirdCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFlappyBirdCharacter::TouchStopped);
}
*/

void AFlappyBirdCharacter::StartJump()
{
	// Jump on any touch
	Jump();
}

void AFlappyBirdCharacter::StopJump()
{
	StopJumping();
}


void AFlappyBirdCharacter::MoveToRight()
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementAmount);
	FVector CharLoc = GetActorLocation();
	if (CharLoc.X > BoundaryRightX)
	{
		SetActorLocation(FVector(BoundaryLeftX, CharLoc.Y, CharLoc.Z));
		OnCharacterGoesToLeftBoundary.Broadcast(BoundaryLeftX);
	}
}

void AFlappyBirdCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

// Begin Play
void AFlappyBirdCharacter::BeginPlay()
{
	Super::BeginPlay();
	AFlappyBirdPlayerController* theCtrlr = Cast<AFlappyBirdPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(theCtrlr))
	{
		CtrlRef = theCtrlr;
		CtrlRef->OnPlayerPressJump.AddDynamic(this, &AFlappyBirdCharacter::StartJump);
		CtrlRef->OnPlayerReleaseJump.AddDynamic(this, &AFlappyBirdCharacter::StopJump);
		CtrlRef->OnPlayerStartedInput.AddDynamic(this, &AFlappyBirdCharacter::PlayerStartedInput);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerMoveRight, this, &AFlappyBirdCharacter::MoveToRight, MovementFrequency, true);
	theCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFlappyBirdCharacter::CollisionOverlapStart);
}

void AFlappyBirdCharacter::PlayerStartedInput()
{
	ChMovement->GravityScale = 2.0f;
}

void AFlappyBirdCharacter::CollisionOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintOnScreen("Overlap");
	AActor* desiredActor;
	AActor* hitActor = SweepResult.GetActor();
	if (hitActor == this)
	{
		desiredActor = OtherActor;
	}
	else
	{
		desiredActor = hitActor;
	}
	ABarrierPaperSpriteActor* barrier = Cast<ABarrierPaperSpriteActor>(desiredActor);
	if (IsValid(barrier))
	{
		Destroy();
	}
}
