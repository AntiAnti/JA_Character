// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include "Lightsaber.h"
#include "AcademyCharacter.h"


// Sets default values
AAcademyCharacter::AAcademyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	fCurrentSpeed = 400.0f;
	fSpeedMultiplier = 1.0f;
	IsJumping = false;
	IsNPC = false;

	CharacterTeam = ECharacterTeam::T_NoInfo;

	MainParams.Add(FCharacterParameter("Health", 1.0f));
	MainParams.Add(FCharacterParameter("Shields", 1.0f));
	MainParams.Add(FCharacterParameter("Strength", 1.0f));
	Ind_Health = 0;
	Ind_Shields = 1;
	Ind_Strength = 2;
}

// Called when the game starts or when spawned
void AAcademyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAcademyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAcademyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AAcademyCharacter::SetSpeedMultiplier(float Multiplier)
{
	fSpeedMultiplier = Multiplier;
	GetCharacterMovement()->MaxWalkSpeed = fCurrentSpeed * fSpeedMultiplier;
}