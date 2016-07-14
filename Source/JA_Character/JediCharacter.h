// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AcademyCharacter.h"
#include "JediCharacter.generated.h"

class ULightsaber;
class ALightsaberActor;

/**
 * 
 */
UCLASS(Blueprintable)
class JA_CHARACTER_API AJediCharacter : public AAcademyCharacter
{
	GENERATED_BODY()

public:
	AJediCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UBoxComponent* LocomotionTrigger_Front;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UBoxComponent* LocomotionTrigger_Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UBoxComponent* LocomotionTrigger_Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	USphereComponent* ProtectingColliderTop;

	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	ULightsaber* SaberLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	ULightsaber* SaberRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UParticleSystemComponent* ps_SaberLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UParticleSystemComponent* ps_SaberRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UPointLightComponent* Light_SaberLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UPointLightComponent* Light_SaberRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UCapsuleComponent* Collider_SaberLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	UCapsuleComponent* Collider_SaberRight;
	*/

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// VARIABLES /////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	ESideToCharacter LocomotionObstacle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	bool MovementInputEnabled;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	bool IsSaberAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	bool IsSaberDefending;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	uint8 LightsaberStyle;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	FVector SaberDefenceOffset;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	float SimpleAttackDirection;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	FVector SimpleAttackLookAt;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	FVector IK_OffsetRight;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	FVector IK_OffsetLeft;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	bool IK_CollidingRight;

	UPROPERTY(BlueprintReadWrite, Category = "Jedi")
	bool IK_CollidingLeft;

	/* AAcademyCharacter::ArmingState  */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	ELightsabersArming SabersAvalible;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	bool LightsaberAvalible1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	bool LightsaberAvalible2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	bool LightsaberAvalibleDual;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	FLinearColor FirstSaberColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	FLinearColor SecondSaberColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	UStaticMesh* FirstSaberHandleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	UStaticMesh* SecondSaberHandleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	float SaberResponseEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	float SaberStrengthMultiplier;

	UPROPERTY(BlueprintReadWrite, Category = "Character Arming")
	ALightsaberActor* FirstLightsaber;

	UPROPERTY(BlueprintReadWrite, Category = "Character Arming")
	ALightsaberActor* SecondLightsaber;

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////// FORCES //////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jedi")
	EForceIntensity Force_Jump;
	////////////////////////////////////// FORCES //////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// FUNCTIONS /////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	bool SetSaberArmingState(ELightsabersArming NewState);

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	void RecalcAttackDirectionAndBodyRotation(FVector EnemyLocation);

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	uint8 GetSabersCount();

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	float GetSabersStyleCode();

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	void SetForceJump(EForceIntensity Value);

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	void SetEnableLightsabersTrail(bool IsTrailEnabled);

	UFUNCTION(BlueprintCallable, Category = "Jedi")
	void StartSaberAttack() { IsSaberAttacking = true; IsSaberDefending = false; };

	UFUNCTION(BlueprintNativeEvent, Category = "Jedi")
	void OnSabersCollided();
	virtual void OnSabersCollided_Implementation() {};

protected:
	UFUNCTION(BlueprintCallable, Category = "Constructor")
	void InitLightsaber();

	UFUNCTION()
	void OnBeginOverlap_LeftTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap_LeftTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap_RightTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap_RightTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap_FrontTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap_FrontTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap_ProtectorTop(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap_ProtectorTop(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
