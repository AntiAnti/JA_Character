// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "JA_CharacterGameMode.generated.h"

UCLASS(minimalapi)
class AJA_CharacterGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AJA_CharacterGameMode();

	UFUNCTION(Exec)
	void setforcejump(uint8 level);

	UFUNCTION(Exec)
	void twosabers();

	UFUNCTION(Exec)
	void onesaber();

	UFUNCTION(Exec)
	void saberstyle(uint8 number);
};



