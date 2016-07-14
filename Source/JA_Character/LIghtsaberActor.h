// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LightsaberActor.generated.h"

class AJediCharacter;

UCLASS()
class JA_CHARACTER_API ALightsaberActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightsaberActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

	//////////////////////////////////// COMPONENTS ////////////////////////////////////
	UPROPERTY(VisibleDefaultsOnly, Category = "Lightsaber")
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	UStaticMeshComponent* SaberHandleMesh;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystemComponent* MainBladeEmitter;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UPointLightComponent* MainBladePointLight;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UCapsuleComponent* MainBladeCollider;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystemComponent* MainBladeAnimTrail;

	// two-bladed saber
	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystemComponent* SecondaryBladeEmitter;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UPointLightComponent* SecondaryBladePointLight;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UCapsuleComponent* SecondaryBladeCollider;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystemComponent* SecondaryBladeAnimTrail;

public:
	//////////////////////////////////// GLOBAL VARIABLES ////////////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	ALightsaberActor* FriendlyActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	AJediCharacter* OwnerJediCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	FLinearColor MainBladeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	FLinearColor SecondaryBladeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	bool IsTwoBladed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	float SaberLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	bool IsRightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	bool IsInitialized;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	bool IsEnabled;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystem* PS_SaberCollide;

	UPROPERTY(BlueprintReadWrite, Category = "Lightsaber")
	UParticleSystem* PS_WallCollide;

	UPROPERTY()
	UParticleSystemComponent* MainBurstEmitter;
	UPROPERTY()
	TEnumAsByte<ECollisionChannel> MainBurstEmitterObjectType;

	UPROPERTY()
	UParticleSystemComponent* SecondaryBurstEmitter;
	UPROPERTY()
	TEnumAsByte<ECollisionChannel> SecondaryBurstEmitterObjectType;

	UPROPERTY()
	int8 EmittersCount;

	UPROPERTY()
	FTimerHandle MainEmitterDestroyTimer;
	UPROPERTY()
	FTimerHandle SecondaryEmitterDestroyTimer;

public:
	//////////////////////////////////// PARAMETERS ////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	float ResponseEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightsaber")
	float StrengthMultiplier;

public:
	//////////////////////////////////// FUNCTIONS ////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	bool AttachSaberToJediCharacter(AJediCharacter* character, bool RightHand = true);


	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void SetSaberEnabled(bool NewEnabled);

	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	bool GetSaberEnabled() { return IsEnabled; };

	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void InitialUpdate();

	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void EnableTrails(bool IsTrailEnabled);

protected:
	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void SetBladesVisibility();

	UFUNCTION(BlueprintCallable, Category = "Lightsaber")
	void SetBladesColor();

	//////////////////////////////////// EVENTS ////////////////////////////////////
	UFUNCTION()
	FVector TraceSaberBladeToObject(ECollisionChannel ObjectType, bool IsMain);

	UFUNCTION()
	void SetEmitterLifeSpan(bool IsMain, float LifeSpan);

	UFUNCTION()
	void OnLifeSpanTimerMain();
	UFUNCTION()
	void OnLifeSpanTimerSecondary();

	UFUNCTION()
	void OnBladeBeginOverlap1(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBladeEndOverlap1(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnBladeBeginOverlap2(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBladeEndOverlap2(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnBladeBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool IsMain);
	UFUNCTION()
	void OnBladeEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool IsMain);
};
