// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Navigation/NavAreas/NavArea.h"
#include "Runtime/Engine/Classes/AI/Navigation/RecastNavMesh.h"
#include "NavArea_Jump.generated.h"

UENUM()
namespace ENavAreaFlag
{
	enum Type
	{
		Default,
		JumpNoForce,
		JumpForce1,
		JumpForce2,
		JumpForce3,
		Sidewalk,
		SidewalkToRoof
	};
}

namespace FNavAreaHelper
{
	FORCEINLINE bool IsSet(uint16 Flags, ENavAreaFlag::Type Bit) { return (Flags & (1 << Bit)) != 0; }
	FORCEINLINE void Set(uint16& Flags, ENavAreaFlag::Type Bit) { Flags |= (1 << Bit); }

	FORCEINLINE bool IsNavLink(const FNavPathPoint& PathVert) { return (FNavMeshNodeFlags(PathVert.Flags).PathFlags & RECAST_STRAIGHTPATH_OFFMESH_CONNECTION) != 0; }
	FORCEINLINE bool HasJumpFlag(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpNoForce) || IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce1) || IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce2) || IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce3); }
	FORCEINLINE bool HasJumpNoForce(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpNoForce); }
	FORCEINLINE bool HasJumpFlag1(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce1); }
	FORCEINLINE bool HasJumpFlag2(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce2); }
	FORCEINLINE bool HasJumpFlag3(const FNavPathPoint& PathVert) { return IsSet(FNavMeshNodeFlags(PathVert.Flags).AreaFlags, ENavAreaFlag::JumpForce3); }
}

/**
 * 
 */
UCLASS()
class JA_CHARACTER_API UNavArea_Jump : public UNavArea
{
	GENERATED_BODY()

	UNavArea_Jump();
};
