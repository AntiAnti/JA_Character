// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "JA_Character.h"
#include "JA_CharacterGameMode.h"
#include "AcademyCharacter.h"
#include "JediCharacter.h"
#include "JA_CharacterCharacter.h"

AJA_CharacterGameMode::AJA_CharacterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AJA_CharacterGameMode::setforcejump(uint8 level)
{
	EForceIntensity val;
	switch (level) {
	case 0: val = EForceIntensity::I_NoForce; break;
	case 1: val = EForceIntensity::I_Level1; break;
	case 2: val = EForceIntensity::I_Level2; break;
	case 3: val = EForceIntensity::I_Level3; break;
	default: val = EForceIntensity::I_Level1; break;
	}

	Cast<AJediCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->SetForceJump(val);
}

void AJA_CharacterGameMode::twosabers()
{
	AJediCharacter* player = Cast<AJediCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(player)) {
		player->SabersAvalible = ELightsabersArming::PairedSabers;
		player->SetSaberArmingState(ELightsabersArming::PairedSabers);
	}
}

void AJA_CharacterGameMode::onesaber()
{
	AJediCharacter* player = Cast<AJediCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(player)) {
		player->SabersAvalible = ELightsabersArming::SaberSingle;
		player->SetSaberArmingState(ELightsabersArming::SaberSingle);
	}
}

void AJA_CharacterGameMode::saberstyle(uint8 number)
{
	AJediCharacter* player = Cast<AJediCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (IsValid(player)) {
		if (number > 3) number = 3;
		player->LightsaberStyle = number + 1;
	}
}
