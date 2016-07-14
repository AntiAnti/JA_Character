// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include "NavArea_Jump.h"


UNavArea_Jump::UNavArea_Jump()
{
	FNavAreaHelper::Set(AreaFlags, ENavAreaFlag::JumpForce2);
}