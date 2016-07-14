// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"
#include "AIPathFollowingComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JA_CHARACTER_API UAIPathFollowingComponent : public UPathFollowingComponent
{
	GENERATED_BODY()
	
protected:
	/** cached UCharacterMovementComponent */
	UPROPERTY(transient)
	UCharacterMovementComponent* CharacterMoveComp;

	void MakeJump();

public:
	UAIPathFollowingComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Path Following")
	uint8 JumpingForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Path Following")
	bool IsCanJump;

	// used to detect properties of a path's segment a character is about to follow
	virtual void SetMoveSegment(int32 SegmentStartIndex) override;

	// used to cache UCharacterMovementComponent we're using in SetMoveSegment implementation
	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;
};
