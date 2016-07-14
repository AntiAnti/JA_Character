// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include "NavArea_Jump.h"
#include "Engine.h"
#include "AcademyCharacter.h"
#include "AIPathFollowingComponent.h"

UAIPathFollowingComponent::UAIPathFollowingComponent()
{
	JumpingForce = 2;
	IsCanJump = true;
}

void UAIPathFollowingComponent::SetMoveSegment(int32 SegmentStartIndex)
{
	Super::SetMoveSegment(SegmentStartIndex);

	if (CharacterMoveComp != NULL)
	{
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[MoveSegmentStartIndex];

		if (IsCanJump)
		{
			if (FNavAreaHelper::HasJumpNoForce(SegmentStart)) {
				MakeJump();
			}
			else if (FNavAreaHelper::HasJumpFlag1(SegmentStart) && JumpingForce >= 1) {
				MakeJump();
			}
			else if (FNavAreaHelper::HasJumpFlag2(SegmentStart) && JumpingForce >= 2) {
				/*
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("I AM JUMPING!"));
				Cast<ACharacter>(CharacterMoveComp->GetPawnOwner())->Jump();
				*/
				MakeJump();
			}
			else if (FNavAreaHelper::HasJumpFlag3(SegmentStart) && JumpingForce >= 3) {
				MakeJump();
			}
			else {
				CharacterMoveComp->SetMovementMode(MOVE_Walking);
			}
		}
		else
		{
			// regular move
			CharacterMoveComp->SetMovementMode(MOVE_Walking);
		}
	}
}

void UAIPathFollowingComponent::MakeJump()
{
	AAcademyCharacter* character = Cast<AAcademyCharacter>(CharacterMoveComp->GetPawnOwner());

	if (IsValid(character)) {
		//CharacterMoveComp->SetMovementMode(MOVE_Flying);
		character->Jump();
		character->IsJumping = true;
	}
}

void UAIPathFollowingComponent::SetMovementComponent(UNavMovementComponent* MoveComp)
{
	Super::SetMovementComponent(MoveComp);

	CharacterMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
}