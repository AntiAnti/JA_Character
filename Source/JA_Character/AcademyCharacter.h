// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AcademyCharacter.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EForcePower : uint8
{
	F_Jump				UMETA(DisplayName = "Jump"),
	F_ProtectNear		UMETA(DisplayName = "ProtectNear"),
	F_ProtectFar		UMETA(DisplayName = "ProtectFar"),
	F_Pull				UMETA(DisplayName = "Pull"),
	F_Push				UMETA(DisplayName = "Push"),
	F_TimeWrap			UMETA(DisplayName = "TimeWrap"),
	F_Heal				UMETA(DisplayName = "Heal"),
	F_Protect			UMETA(DisplayName = "Protect"),
	F_Adsorb			UMETA(DisplayName = "Adsorb"),
	F_Lightning			UMETA(DisplayName = "Lightning"),
	F_Grip				UMETA(DisplayName = "Grip"),
	F_Drain				UMETA(DisplayName = "Drain"),
	F_DarkRage			UMETA(DisplayName = "DarkRage")
};

UENUM(BlueprintType, Blueprintable)
enum class EForceIntensity : uint8
{
	I_NoForce			UMETA(DisplayName = "NoForce"),
	I_Level1			UMETA(DisplayName = "Level 1"),
	I_Level2			UMETA(DisplayName = "Level 2"),
	I_Level3			UMETA(DisplayName = "Level 3")
};

UENUM(BlueprintType, Blueprintable)
enum class ESpecialMovement : uint8
{
	M_None				UMETA(DisplayName = "None"),
	M_Roll				UMETA(DisplayName = "Roll"),
	M_Hop				UMETA(DisplayName = "Hop")
};

UENUM(BlueprintType, Blueprintable)
enum class ESideToCharacter : uint8
{
	S_None				UMETA(DisplayName = "None"),
	S_Front				UMETA(DisplayName = "Front"),
	S_Right				UMETA(DisplayName = "Right"),
	S_Back				UMETA(DisplayName = "Back"),
	S_Left				UMETA(DisplayName = "Left")
};

UENUM(BlueprintType, Blueprintable)
enum class ELightsabersArming : uint8
{
	NoSaber					UMETA(DisplayName = "No Saber"),
	SaberSingle				UMETA(DisplayName = "Single Blade"),
	SaberDualBladed			UMETA(DisplayName = "Dual Blade"),
	PairedSabers			UMETA(DisplayName = "Two Paired Sabers"),
	GunSingle				UMETA(DisplayName = "Single Gun"),
	GunTwoHanded			UMETA(DisplayName = "Two Handed Gun"),
	PairedGuns				UMETA(DisplayName = "Two Paired Guns")
};

UENUM(BlueprintType, Blueprintable)
enum class ECharacterTeam : uint8
{
	T_NoInfo				UMETA(DisplayName = "No Info"),
	T_Team1					UMETA(DisplayName = "Team 1"),
	T_Team2					UMETA(DisplayName = "Team 2"),
	T_Team3					UMETA(DisplayName = "Team 3"),
	T_Team4					UMETA(DisplayName = "Team 4"),
	T_Team5					UMETA(DisplayName = "Team 5")
};

USTRUCT(BlueprintType, Blueprintable)
struct FForceDescription
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EForcePower ForceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EForceIntensity Intensity;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterParameter
{
	GENERATED_USTRUCT_BODY()

	FCharacterParameter() { ParamName = ""; Value = 0.0f; };
	FCharacterParameter(FString NewParamName, float NewValue) { ParamName = NewParamName; Value = NewValue; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

UCLASS(Blueprintable)
class JA_CHARACTER_API AAcademyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAcademyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// VARIABLES /////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float fDirectionKey;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float fCurrentSpeed;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float fSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Arming")
	ELightsabersArming ArmingState;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	ECharacterTeam CharacterTeam;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	bool IsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool IsNPC;

	//------------------ Набор базовых параметров персонажа: сила, здоровье и т. д.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<FCharacterParameter> MainParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Params")
	uint8 Ind_Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Params")
	uint8 Ind_Shields;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Params")
	uint8 Ind_Strength;
	//------------------

	//////////////////////////////////// VARIABLES /////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////// FORCES //////////////////////////////////////

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	ESpecialMovement CurrentMovement;

	////////////////////////////////////// FORCES //////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////// OVERRIDES /////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual float GetDirectionKey() { return fDirectionKey; };

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetDirectionKey(float NewValue) { fDirectionKey = NewValue; };

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetSpeedMultiplier(float Multiplier);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void ResetCurrentMovementState() { CurrentMovement = ESpecialMovement::M_None; SetSpeedMultiplier(1.0f); };


	UFUNCTION(BlueprintCallable, Category = "Character")
	bool IsEnemy(AAcademyCharacter* OtherCharacter) { return (OtherCharacter->GetCharacterTeam() != this->GetCharacterTeam()); };

	UFUNCTION(BlueprintNativeEvent, Category = "Character")
	void OnDamage(float Damage);
	virtual void OnDamage_Implementation(float Damage) {};

	UFUNCTION(BlueprintCallable, Category = "Character")
	ECharacterTeam GetCharacterTeam() { return CharacterTeam; };

	//////////////////////////////////// OVERRIDES /////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
};
