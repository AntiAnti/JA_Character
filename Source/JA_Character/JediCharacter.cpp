// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include <Kismet/KismetMathLibrary.h>
#include <Engine.h>
#include "Lightsaber.h"
#include "LIghtsaberActor.h"
#include "JediCharacter.h"

AJediCharacter::AJediCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> smAsset(TEXT("SkeletalMesh'/Game/JA/SkeletalMeshes/sm_Humanoid_Kyle.sm_Humanoid_Kyle'"));
	if (smAsset.Object != NULL) this->GetMesh()->SetSkeletalMesh(smAsset.Object);
	GetMesh()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	
	LocomotionTrigger_Front = CreateDefaultSubobject<UBoxComponent>(TEXT("LocomotionTrigger_Front"));
	LocomotionTrigger_Front->SetupAttachment(GetCapsuleComponent());
	LocomotionTrigger_Front->SetRelativeLocation(FVector(150.0f, 0.0f, 50.0f));
	LocomotionTrigger_Front->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	LocomotionTrigger_Front->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LocomotionTrigger_Front->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocomotionTrigger_Front->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Front->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Front->OnComponentBeginOverlap.AddDynamic(this, &AJediCharacter::OnBeginOverlap_FrontTrigger);
	LocomotionTrigger_Front->OnComponentEndOverlap.AddDynamic(this, &AJediCharacter::OnEndOverlap_FrontTrigger);

	LocomotionTrigger_Left = CreateDefaultSubobject<UBoxComponent>(TEXT("LocomotionTrigger_Left"));
	LocomotionTrigger_Left->SetupAttachment(GetCapsuleComponent());
	LocomotionTrigger_Left->SetRelativeLocation(FVector(0.0f, -130.0f, 50.0f));
	LocomotionTrigger_Left->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	LocomotionTrigger_Left->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LocomotionTrigger_Left->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocomotionTrigger_Left->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Left->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Left->OnComponentBeginOverlap.AddDynamic(this, &AJediCharacter::OnBeginOverlap_LeftTrigger);
	LocomotionTrigger_Left->OnComponentEndOverlap.AddDynamic(this, &AJediCharacter::OnEndOverlap_LeftTrigger);

	LocomotionTrigger_Right = CreateDefaultSubobject<UBoxComponent>(TEXT("LocomotionTrigger_Right"));
	LocomotionTrigger_Right->SetupAttachment(GetCapsuleComponent());
	LocomotionTrigger_Right->SetRelativeLocation(FVector(0.0f, 130.0f, 50.0f));
	LocomotionTrigger_Right->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	LocomotionTrigger_Right->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LocomotionTrigger_Right->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LocomotionTrigger_Right->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Right->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	LocomotionTrigger_Right->OnComponentBeginOverlap.AddDynamic(this, &AJediCharacter::OnBeginOverlap_RightTrigger);
	LocomotionTrigger_Right->OnComponentEndOverlap.AddDynamic(this, &AJediCharacter::OnEndOverlap_RightTrigger);

	ProtectingColliderTop = CreateDefaultSubobject<USphereComponent>(TEXT("ProtectingColliderTop"));
	ProtectingColliderTop->SetupAttachment(GetCapsuleComponent());
	ProtectingColliderTop->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));
	ProtectingColliderTop->SetSphereRadius(105.0f);
	ProtectingColliderTop->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProtectingColliderTop->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ProtectingColliderTop->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ProtectingColliderTop->SetCollisionResponseToChannel(EEC_LightsaberChannel, ECollisionResponse::ECR_Overlap);
	ProtectingColliderTop->OnComponentBeginOverlap.AddDynamic(this, &AJediCharacter::OnBeginOverlap_ProtectorTop);
	ProtectingColliderTop->OnComponentEndOverlap.AddDynamic(this, &AJediCharacter::OnEndOverlap_ProtectorTop);
	

	/*
	SaberLeft = CreateDefaultSubobject<ULightsaber>(TEXT("SaberLeft"));
	SaberLeft->AttachTo(GetMesh(), TEXT("Saber_Left"));
	SaberLeft->SetRelativeLocation(FVector(0.126247f, 0.0f, 0.0f));
	SaberLeft->SetRelativeRotation(FRotator(90.0f, -5.0f, -5.0f).Quaternion());
	SaberLeft->SetRelativeScale3D(FVector(0.07f, 0.07f, 0.07f));

	SaberRight = CreateDefaultSubobject<ULightsaber>(TEXT("SaberRight"));
	SaberRight->AttachTo(GetMesh(), TEXT("Saber_Right"));
	SaberRight->SetRelativeLocation(FVector(0.126247f, 0.0f, 0.0f));
	SaberRight->SetRelativeRotation(FRotator(90.0f, -5.0f, -5.0f).Quaternion());
	SaberRight->SetRelativeScale3D(FVector(0.07f, 0.07f, 0.07f));

	ps_SaberLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ps_SaberLeft"));
	ps_SaberLeft->AttachParent = SaberLeft;
	ps_SaberLeft->SetRelativeLocation(FVector(0.0f, 0.0f, 55.0f));
	ps_SaberLeft->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	ps_SaberLeft->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	ps_SaberRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ps_SaberRight"));
	ps_SaberRight->AttachParent = SaberRight;
	ps_SaberRight->SetRelativeLocation(FVector(0.0f, 0.0f, 55.0f));
	ps_SaberRight->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	ps_SaberRight->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	Light_SaberLeft = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light_SaberLeft"));
	Light_SaberLeft->AttachParent = SaberLeft;
	Light_SaberLeft->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	Light_SaberLeft->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f).Quaternion());
	Light_SaberLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Light_SaberLeft->Intensity = 1000.0f;
	Light_SaberLeft->AttenuationRadius = 612.0f;
	Light_SaberLeft->SourceLength = 70.0f;

	Light_SaberRight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light_SaberRight"));
	Light_SaberRight->AttachParent = SaberRight;
	Light_SaberRight->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	Light_SaberRight->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f).Quaternion());
	Light_SaberRight->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Light_SaberRight->Intensity = 1000.0f;
	Light_SaberRight->AttenuationRadius = 612.0f;
	Light_SaberRight->SourceLength = 70.0f;

	Collider_SaberLeft = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider_SaberLeft"));
	Collider_SaberLeft->AttachParent = SaberLeft;
	Collider_SaberLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Collider_SaberLeft->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
	Collider_SaberLeft->SetRelativeRotation(FRotator::ZeroRotator);
	Collider_SaberLeft->SetCapsuleHalfHeight(196.0f);
	Collider_SaberLeft->SetCapsuleRadius(15.0f);
	Collider_SaberLeft->SetCollisionObjectType(EEC_LightsaberChannel);
	Collider_SaberLeft->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider_SaberLeft->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider_SaberLeft->SetCollisionResponseToChannel(EEC_LightsaberChannel, ECollisionResponse::ECR_Block);
	Collider_SaberLeft->SetNotifyRigidBodyCollision(true);

	Collider_SaberRight = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider_SaberRight"));
	Collider_SaberRight->AttachParent = SaberRight;
	Collider_SaberRight->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Collider_SaberRight->SetRelativeLocation(FVector(0.0f, 0.0f, 230.0f));
	Collider_SaberRight->SetRelativeRotation(FRotator::ZeroRotator);
	Collider_SaberRight->SetCapsuleHalfHeight(196.0f);
	Collider_SaberRight->SetCapsuleRadius(15.0f);
	Collider_SaberRight->SetCollisionObjectType(EEC_LightsaberChannel);
	Collider_SaberRight->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider_SaberRight->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collider_SaberRight->SetCollisionResponseToChannel(EEC_LightsaberChannel, ECollisionResponse::ECR_Block);
	Collider_SaberRight->SetNotifyRigidBodyCollision(true);

	SaberLeft->BladeParticleSystem = ps_SaberLeft;
	SaberRight->BladeParticleSystem = ps_SaberRight;
	*/

	MovementInputEnabled = true;
	/*
	LightsaberAvalible1 = true;
	LightsaberAvalible2 = true;
	LightsaberAvalibleDual = false;
	*/
	SabersAvalible = ELightsabersArming::PairedSabers;
	LightsaberStyle = 0;

	FirstSaberColor = FLinearColor(0.13f, 0.15f, 1.0f);
	SecondSaberColor = FLinearColor(0.13f, 0.15f, 1.0f);
	FirstSaberHandleMesh = nullptr;
	SecondSaberHandleMesh = nullptr;
	SaberResponseEfficiency = 0.65f;
	SaberStrengthMultiplier = 1.0f;

	ArmingState = ELightsabersArming::SaberSingle;
}

void AJediCharacter::BeginPlay()
{
	Super::BeginPlay();

	//SaberLeft->BladeParticleSystem = ps_SaberLeft;
	//SaberRight->BladeParticleSystem = ps_SaberRight;

	InitLightsaber();
}

void AJediCharacter::InitLightsaber()
{
	FTransform tr;
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if ((SabersAvalible == ELightsabersArming::SaberSingle || SabersAvalible == ELightsabersArming::PairedSabers || SabersAvalible == ELightsabersArming::SaberDualBladed) && !IsValid(FirstLightsaber)) {
		tr = GetMesh()->GetSocketTransform(SOCKET_Saber_Right);
		tr.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		FirstLightsaber = GetWorld()->SpawnActor<ALightsaberActor>(ALightsaberActor::StaticClass(), tr, param);

		if (IsValid(FirstLightsaber)) {
			FirstLightsaber->AttachSaberToJediCharacter(this, true);
			FirstLightsaber->MainBladeColor = FirstSaberColor;
			FirstLightsaber->ResponseEfficiency = SaberResponseEfficiency;
			FirstLightsaber->StrengthMultiplier = SaberStrengthMultiplier;
			if (IsValid(FirstSaberHandleMesh)) FirstLightsaber->SaberHandleMesh->SetStaticMesh(FirstSaberHandleMesh);
			if (SabersAvalible == ELightsabersArming::SaberDualBladed) {
				FirstLightsaber->IsTwoBladed = true;
				FirstLightsaber->SecondaryBladeColor = SecondSaberColor;
			}
			FirstLightsaber->SetSaberEnabled(ArmingState != ELightsabersArming::NoSaber);
			FirstLightsaber->InitialUpdate();
			FirstLightsaber->IsRightHand = true;
			FirstLightsaber->IsInitialized = true;
		}
	}

	if ((SabersAvalible == ELightsabersArming::PairedSabers) && !IsValid(SecondLightsaber)) {
		tr = GetMesh()->GetSocketTransform(SOCKET_Saber_Left);
		tr.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
		SecondLightsaber = GetWorld()->SpawnActor<ALightsaberActor>(ALightsaberActor::StaticClass(), tr, param);

		if (IsValid(SecondLightsaber)) {
			SecondLightsaber->AttachSaberToJediCharacter(this, false);
			SecondLightsaber->MainBladeColor = SecondSaberColor;
			SecondLightsaber->ResponseEfficiency = SaberResponseEfficiency;
			SecondLightsaber->StrengthMultiplier = SaberStrengthMultiplier;
			if (IsValid(SecondSaberHandleMesh)) SecondLightsaber->SaberHandleMesh->SetStaticMesh(SecondSaberHandleMesh);
			SecondLightsaber->SetSaberEnabled(ArmingState == ELightsabersArming::PairedSabers);
			SecondLightsaber->InitialUpdate();

			FirstLightsaber->FriendlyActor = SecondLightsaber;
			SecondLightsaber->FriendlyActor = FirstLightsaber;
			SecondLightsaber->IsRightHand = false;
			SecondLightsaber->IsInitialized = true;
		}
	}
}

bool AJediCharacter::SetSaberArmingState(ELightsabersArming NewState)
{
	bool bRet = false;
	InitLightsaber();

	if (NewState == ELightsabersArming::NoSaber || SabersAvalible == ELightsabersArming::NoSaber) {
		if (IsValid(FirstLightsaber))
			FirstLightsaber->SetSaberEnabled(false);
		if (IsValid(SecondLightsaber))
			SecondLightsaber->SetSaberEnabled(false);

		bRet = (ELightsabersArming::NoSaber == NewState);
		ArmingState = ELightsabersArming::NoSaber;
	}
	else if ((NewState == ELightsabersArming::SaberSingle && SabersAvalible != ELightsabersArming::NoSaber) || (NewState == ELightsabersArming::PairedSabers && SabersAvalible != ELightsabersArming::PairedSabers) || (NewState == ELightsabersArming::SaberDualBladed && SabersAvalible == ELightsabersArming::SaberDualBladed)) {
		if (IsValid(FirstLightsaber))
			FirstLightsaber->SetSaberEnabled(true);
		if (IsValid(SecondLightsaber))
			SecondLightsaber->SetSaberEnabled(false);

		if (NewState == ELightsabersArming::SaberDualBladed)
			ArmingState = ELightsabersArming::SaberDualBladed;
		else
			ArmingState = ELightsabersArming::SaberSingle;

		bRet = (ELightsabersArming::SaberSingle == NewState);;
	}
	else if (NewState == ELightsabersArming::PairedSabers && SabersAvalible == ELightsabersArming::PairedSabers) {
		if (IsValid(FirstLightsaber))
			FirstLightsaber->SetSaberEnabled(true);
		if (IsValid(SecondLightsaber))
			SecondLightsaber->SetSaberEnabled(true);

		ArmingState = ELightsabersArming::PairedSabers;
		bRet = (ELightsabersArming::PairedSabers == NewState);
	}
	else {
		ArmingState = NewState;
	}

	return bRet;
}

void AJediCharacter::RecalcAttackDirectionAndBodyRotation(FVector EnemyLocation)
{
	SimpleAttackLookAt = EnemyLocation;

	SimpleAttackDirection = FMath::RandRange(-90.0f, 90.0f);
}

void AJediCharacter::OnBeginOverlap_LeftTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (!GetCharacterMovement()->IsFalling())
		LocomotionObstacle = ESideToCharacter::S_Left;
}

void AJediCharacter::OnEndOverlap_LeftTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	LocomotionObstacle = ESideToCharacter::S_None;
}

void AJediCharacter::OnBeginOverlap_RightTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (!GetCharacterMovement()->IsFalling())
		LocomotionObstacle = ESideToCharacter::S_Right;
}

void AJediCharacter::OnEndOverlap_RightTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	LocomotionObstacle = ESideToCharacter::S_None;
}

void AJediCharacter::OnBeginOverlap_FrontTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (!GetCharacterMovement()->IsFalling()) {
		LocomotionObstacle = ESideToCharacter::S_Front;
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("ON"));
	}
}

void AJediCharacter::OnEndOverlap_FrontTrigger(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(FirstLightsaber) && FirstLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(SecondLightsaber) && SecondLightsaber->GetUniqueID() == OtherActor->GetUniqueID()) return;
	LocomotionObstacle = ESideToCharacter::S_None;
}

void AJediCharacter::OnBeginOverlap_ProtectorTop(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsSaberAttacking && IsValid(FirstLightsaber) && OtherActor->GetUniqueID() != FirstLightsaber->GetUniqueID()) {
		if (!IsValid(SecondLightsaber) || OtherActor->GetUniqueID() != SecondLightsaber->GetUniqueID()) {
			FRotator rToSaber = UKismetMathLibrary::FindLookAtRotation(ProtectingColliderTop->GetComponentLocation(), OtherComp->GetComponentLocation());
			FTransform tWorld = FTransform(rToSaber, ProtectingColliderTop->GetComponentLocation(), FVector(1.0f, 1.0f, 1.0f));
			FTransform tLocal = UKismetMathLibrary::ConvertTransformToRelative(tWorld, ProtectingColliderTop->GetComponentTransform());
			SaberDefenceOffset.Y = tLocal.Rotator().Yaw;
			SaberDefenceOffset.Z = tLocal.Rotator().Pitch;

			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, this->GetActorLabel() + " attacked by " + OtherActor->GetActorLabel());
			IsSaberDefending = true;
		}
	}
}

void AJediCharacter::OnEndOverlap_ProtectorTop(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(FirstLightsaber) && OtherActor->GetUniqueID() != FirstLightsaber->GetUniqueID()) {
		if (!IsValid(SecondLightsaber) || OtherActor->GetUniqueID() != SecondLightsaber->GetUniqueID()) {
			IsSaberDefending = false;
		}
	}
}

float AJediCharacter::GetSabersStyleCode()
{
	/* A1-A3 - стили одного меча, A6 - два меча, A7 - двойной меч */
	/* 0..2 -  стили одного меча, 3 - два меча */

	float fRet = 0.0f;
	if (ArmingState == ELightsabersArming::SaberSingle)
		fRet = (float)LightsaberStyle;
	else if (ArmingState == ELightsabersArming::SaberDualBladed)
		fRet = 3.0f;
	else if (ArmingState == ELightsabersArming::PairedSabers)
		fRet = 4.0f;

	return fRet;
}

void AJediCharacter::SetForceJump(EForceIntensity Value)
{
	Force_Jump = Value;
	if (Value == EForceIntensity::I_NoForce)
		GetCharacterMovement()->JumpZVelocity = 300.0f;
	else if (Value == EForceIntensity::I_Level1)
		GetCharacterMovement()->JumpZVelocity = 600.0f;
	else if (Value == EForceIntensity::I_Level2)
		GetCharacterMovement()->JumpZVelocity = 900.0f;
	else if (Value == EForceIntensity::I_Level3)
		GetCharacterMovement()->JumpZVelocity = 1400.0f;
}

void AJediCharacter::SetEnableLightsabersTrail(bool IsTrailEnabled)
{
	if (IsValid(FirstLightsaber)) FirstLightsaber->EnableTrails(IsTrailEnabled);
	if (IsValid(SecondLightsaber)) SecondLightsaber->EnableTrails(IsTrailEnabled);
}

uint8 AJediCharacter::GetSabersCount()
{
	uint8 ret;

	if (ArmingState == ELightsabersArming::SaberSingle || ArmingState == ELightsabersArming::SaberDualBladed)
		ret = 1;
	else if (ArmingState == ELightsabersArming::PairedSabers)
		ret = 2;
	else
		ret = 0;

	return ret;
}