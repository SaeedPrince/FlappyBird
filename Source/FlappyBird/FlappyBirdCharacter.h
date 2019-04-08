// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "FlappyBirdCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterCrashed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterPassed);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterGoesToLeftBoundary, float, inLeftBoundary);

class AController;
class AFlappyBirdPlayerController;
class AFlappyBirdGameMode;
class UCharacterMovementComponent;
class UPaperFlipbook;
class UTextRenderComponent;

/**
 * This class is the default character for FlappyBird, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class AFlappyBirdCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AFlappyBirdCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	virtual void Tick(float DeltaSeconds) override;

	// Delegates
	/*
	UPROPERTY(BlueprintAssignable, Category = "Map")
		FCharacterGoesToLeftBoundary OnCharacterGoesToLeftBoundary;
	*/

	UPROPERTY(BlueprintAssignable, Category = "Death")
		FCharacterCrashed OnCharacterCrashed;

	UPROPERTY(BlueprintAssignable, Category = "Pass")
		FCharacterPassed OnCharacterPassed;

protected:

	virtual void BeginPlay() override;

	virtual void PossessedBy(class AController* NewController) override;

	void UpdateCharacter();

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	UFUNCTION(BlueprintCallable, Category = "Events")
		void MoveToRight();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void StartJump();

	UFUNCTION(BlueprintCallable, Category = "Events")
		void StopJump();
		
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Events")
		void PrintOnScreen(const FString& inString, bool bScreen = true, bool bLog = true, const FLinearColor& inColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), float inDuration = 8.0f);

	UFUNCTION(BlueprintCallable, Category = "Events")
		void PlayerStartedInput();
		
	UFUNCTION(BlueprintCallable, Category = "Events")
		void CollisionOverlapStart(class UPrimitiveComponent* OverlappedComponent, class  AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(BlueprintReadWrite, Category = "Movement")
		float CurrentMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MovementFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float StartingGravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float PlayingGravity;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boundary")
		float BoundaryLeftX;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boundary")
		float BoundaryRightX;

	UPROPERTY(BlueprintReadWrite, Category = "Timers")
		FTimerHandle TimerMoveRight;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdPlayerController* CtrlRef;

	UPROPERTY(BlueprintReadOnly, Category = "Game Objects")
		class AFlappyBirdGameMode* GameModeRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAudioComponent* GameSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCapsuleComponent* theCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UCharacterMovementComponent* ChMovement;

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Render")
		class UTextRenderComponent* TextComponent;

private:

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;


};
