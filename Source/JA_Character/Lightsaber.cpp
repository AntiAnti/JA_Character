// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include "Engine.h"
#include "Lightsaber.h"


ULightsaber::ULightsaber()
{
	BladeState = false;
}

void ULightsaber::BeginPlay()
{
	Super::BeginPlay();


	SetBladeState(!BladeState);
	SetBladeState(BladeState);
}

void ULightsaber::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	SetBladeState(BladeState);
}

void ULightsaber::SetBladeState(bool NewState)
{
	if (BladeState != NewState) {
		BladeState = NewState;

		if (IsValid(BladeParticleSystem)) {
			BladeParticleSystem->SetVisibility(BladeState);
			//BladeParticleSystem->SetEmitterEnable(TEXT("Blade"), BladeState);
			if (BladeState)
				BladeParticleSystem->Activate();
			else
				BladeParticleSystem->Deactivate();
		}
	}
}
