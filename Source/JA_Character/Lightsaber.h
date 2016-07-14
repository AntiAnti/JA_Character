// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Lightsaber.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class ELightsaberType : uint8
{
	Single				UMETA(DisplayName = "Single Blade"),
	Dual				UMETA(DisplayName = "Dual Blade")
};

/**
 * 
 */
UCLASS(Blueprintable)
class JA_CHARACTER_API ULightsaber : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	ULightsaber();

	virtual void BeginPlay() override;

	void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystemComponent* BladeParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	ELightsaberType LightsaberType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	bool BladeState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	float AttackStrength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	float DefenceStrength;

	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void SetBladeState(bool NewState);
};
