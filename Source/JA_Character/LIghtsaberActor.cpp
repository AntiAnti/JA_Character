// Fill out your copyright notice in the Description page of Project Settings.

#define Blade1_Trail1 TEXT("Blade1_Trail1")
#define Blade1_Trail2 TEXT("Blade1_Trail2")
#define Blade2_Trail1 TEXT("Blade2_Trail1")
#define Blade2_Trail2 TEXT("Blade2_Trail2")

#include "JA_Character.h"
#include "Engine.h"
#include "JediCharacter.h"
#include "LIghtsaberActor.h"

// Sets default values
ALightsaberActor::ALightsaberActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	const float ScaleKoef = 0.21f;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);
	RootSceneComponent->SetRelativeLocation(FVector::ZeroVector);
	RootSceneComponent->SetRelativeRotation(FRotator::ZeroRotator);
	RootSceneComponent->SetRelativeScale3D(FVector(ScaleKoef, ScaleKoef, ScaleKoef));

	SaberHandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SaberHandleMesh"));
	SaberHandleMesh->SetupAttachment(RootSceneComponent);
	SaberHandleMesh->SetRelativeLocation(FVector(0.126247f, 0.0f, 0.0f));
	SaberHandleMesh->SetRelativeRotation(FRotator(90.0f, -5.0f, -5.0f).Quaternion());
	SaberHandleMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	SaberHandleMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	SaberHandleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> smBlade(TEXT("StaticMesh'/Game/JA/MeshesJA/sm_SaberSimple_01.sm_SaberSimple_01'"));
	if (smBlade.Object != NULL) SaberHandleMesh->SetStaticMesh(smBlade.Object);

	MainBladeEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainBladeEmitter"));
	MainBladeEmitter->SetupAttachment(SaberHandleMesh);
	MainBladeEmitter->SetRelativeLocation(FVector(0.0f, 0.0f, 55.0f));
	MainBladeEmitter->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	MainBladeEmitter->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	MainBladeEmitter->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	MainBladeEmitter->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> psSaber(TEXT("ParticleSystem'/Game/JA/FX/Lightsaber_PS.Lightsaber_PS'"));
	if (psSaber.Object != NULL) MainBladeEmitter->SetTemplate(psSaber.Object);

	SecondaryBladeEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SecondaryBladeEmitter"));
	SecondaryBladeEmitter->SetupAttachment(SaberHandleMesh);
	SecondaryBladeEmitter->SetRelativeLocation(FVector(0.0f, 0.0f, -55.0f));
	SecondaryBladeEmitter->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f).Quaternion());
	SecondaryBladeEmitter->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	MainBladeEmitter->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	SecondaryBladeEmitter->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (psSaber.Object != NULL) SecondaryBladeEmitter->SetTemplate(psSaber.Object);

	MainBladePointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MainBladePointLight"));
	MainBladePointLight->SetupAttachment(SaberHandleMesh);
	MainBladePointLight->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	MainBladePointLight->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f).Quaternion());
	MainBladePointLight->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	MainBladePointLight->Intensity = 1000.0f;
	MainBladePointLight->AttenuationRadius = 612.0f;
	MainBladePointLight->SourceLength = 70.0f;

	SecondaryBladePointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("SecondaryBladePointLight"));
	SecondaryBladePointLight->SetupAttachment(SaberHandleMesh);
	SecondaryBladePointLight->SetRelativeLocation(FVector(0.0f, 0.0f, -300.0f));
	SecondaryBladePointLight->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	SecondaryBladePointLight->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	SecondaryBladePointLight->Intensity = 1000.0f;
	SecondaryBladePointLight->AttenuationRadius = 612.0f;
	SecondaryBladePointLight->SourceLength = 70.0f;
	//
	MainBladeCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainBladeCollider"));
	MainBladeCollider->SetupAttachment(SaberHandleMesh);
	//MainBladeCollider->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	MainBladeCollider->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	MainBladeCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 4.76f * 74.0f)); // 230.0f));
	MainBladeCollider->SetRelativeRotation(FRotator::ZeroRotator);
	MainBladeCollider->SetCapsuleHalfHeight(60.0f); // 196.0f);
	MainBladeCollider->SetCapsuleRadius(4.0f);
	MainBladeCollider->SetCollisionObjectType(EEC_LightsaberChannel);
	MainBladeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MainBladeCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MainBladeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	MainBladeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	MainBladeCollider->bMultiBodyOverlap = true;
	MainBladeCollider->SetCollisionResponseToChannel(EEC_LightsaberChannel, ECollisionResponse::ECR_Overlap);
	MainBladeCollider->OnComponentBeginOverlap.AddDynamic(this, &ALightsaberActor::OnBladeBeginOverlap1);
	MainBladeCollider->OnComponentEndOverlap.AddDynamic(this, &ALightsaberActor::OnBladeEndOverlap1);
	MainBladeCollider->bGenerateOverlapEvents = true;

	SecondaryBladeCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SecondaryBladeCollider"));
	SecondaryBladeCollider->SetupAttachment(SaberHandleMesh);
	SecondaryBladeCollider->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	SecondaryBladeCollider->SetRelativeLocation(FVector(0.0f, 0.0f, -4.76f * 74.0f));
	SecondaryBladeCollider->SetRelativeRotation(FRotator::ZeroRotator);
	SecondaryBladeCollider->SetCapsuleHalfHeight(60.0f);
	SecondaryBladeCollider->SetCapsuleRadius(4.0f);
	SecondaryBladeCollider->bMultiBodyOverlap = true;
	SecondaryBladeCollider->SetCollisionObjectType(EEC_LightsaberChannel);
	SecondaryBladeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SecondaryBladeCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SecondaryBladeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	SecondaryBladeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	SecondaryBladeCollider->SetCollisionResponseToChannel(EEC_LightsaberChannel, ECollisionResponse::ECR_Overlap);
	SecondaryBladeCollider->OnComponentBeginOverlap.AddDynamic(this, &ALightsaberActor::OnBladeBeginOverlap2);
	SecondaryBladeCollider->OnComponentEndOverlap.AddDynamic(this, &ALightsaberActor::OnBladeEndOverlap2);
	SecondaryBladeCollider->bGenerateOverlapEvents = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> psSaberTrail(TEXT("ParticleSystem'/Game/ExampleContent/AnimationDemo/Effects/P_AnimTrail_Effect.P_AnimTrail_Effect'"));

	MainBladeAnimTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MainBladeAnimTrail"));
	MainBladeAnimTrail->SetupAttachment(SaberHandleMesh);
	MainBladeAnimTrail->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	MainBladeAnimTrail->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f).Quaternion());
	MainBladeAnimTrail->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	MainBladeAnimTrail->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	MainBladeAnimTrail->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (psSaberTrail.Object != NULL) MainBladeAnimTrail->SetTemplate(psSaberTrail.Object);

	SecondaryBladeAnimTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SecondaryBladeAnimTrail"));
	SecondaryBladeAnimTrail->SetupAttachment(SaberHandleMesh);
	SecondaryBladeAnimTrail->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SecondaryBladeAnimTrail->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f).Quaternion());
	SecondaryBladeAnimTrail->SetRelativeScale3D(FVector(1 / ScaleKoef, 1 / ScaleKoef, 1 / ScaleKoef));
	SecondaryBladeAnimTrail->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	SecondaryBladeAnimTrail->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (psSaberTrail.Object != NULL) SecondaryBladeAnimTrail->SetTemplate(psSaberTrail.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> psSparklesSaber(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_ContinuousBurstYellow.P_ContinuousBurstYellow'"));
	if (psSparklesSaber.Object != NULL) PS_SaberCollide = psSparklesSaber.Object;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> psSparklesWall(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_ContinuousBurstBlue.P_ContinuousBurstBlue'"));
	if (psSparklesWall.Object != NULL) PS_WallCollide = psSparklesWall.Object;

	MainBladeColor = FLinearColor(0.13f, 0.15f, 1.0f);
	SecondaryBladeColor = FLinearColor(0.13f, 0.15f, 1.0f);

	IsTwoBladed = false;
	IsEnabled = true;
	ResponseEfficiency = 0.65f;
	StrengthMultiplier = 1.0f;
	SaberLength = 120.0f;
	EmittersCount = 0;
	IsRightHand = true;
	IsInitialized = false;
	InitialUpdate();
}

// Called when the game starts or when spawned
void ALightsaberActor::BeginPlay()
{
	Super::BeginPlay();
	
	MainBladeAnimTrail->EndTrails();
	SecondaryBladeAnimTrail->EndTrails();
	InitialUpdate();
}

// Called every frame
void ALightsaberActor::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	// Подвигать эмиттеры искр к точке соприкосновения лезвия с чем-то еще
	FVector NewLocation;
	if (IsValid(MainBurstEmitter)) {
		NewLocation = TraceSaberBladeToObject(MainBurstEmitterObjectType, true);
		if (NewLocation != FVector::ZeroVector)
			MainBurstEmitter->SetWorldLocation(NewLocation);
	}
	if (IsValid(SecondaryBurstEmitter)) {
		NewLocation = TraceSaberBladeToObject(SecondaryBurstEmitterObjectType, false);
		if (NewLocation != FVector::ZeroVector)
			SecondaryBurstEmitter->SetWorldLocation(NewLocation);
	}
}

#if WITH_EDITOR
void ALightsaberActor::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SetBladesVisibility();
	SetBladesColor();
}
#endif

bool ALightsaberActor::AttachSaberToJediCharacter(AJediCharacter* character, bool RightHand)
{
	bool bRet = false;

	if (IsValid(character)) {
		OwnerJediCharacter = character;

		FName SocketName;
		if (RightHand) {
			SocketName = SOCKET_Saber_Right;
		}
		else {
			SocketName = SOCKET_Saber_Left;
		}
		FTransform tr = OwnerJediCharacter->GetMesh()->GetSocketTransform(SocketName);
		if (tr.GetLocation() == FVector::ZeroVector && tr.GetTranslation() == FVector::ZeroVector) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Socket not found: " + SocketName.ToString());
		}
		this->SetActorLocation(tr.GetLocation());
		this->SetActorRotation(tr.GetRotation());

		//this->AttachRootComponentToActor(OwnerJediCharacter);
		this->AttachRootComponentTo(OwnerJediCharacter->GetMesh(), SocketName, EAttachLocation::KeepWorldPosition);
		//this->AddActorLocalOffset(FVector(0.126247f, 0.0f, 0.0f));
		//this->AddActorLocalRotation(FRotator(90.0f, -5.0f, -5.0f).Quaternion());

		//this->SetActorRelativeLocation(FVector(0.126247f, 0.0f, 0.0f));
		//this->SetActorRelativeRotation(FRotator(90.0f, -5.0f, -5.0f).Quaternion());
		//SaberHandleMesh->SetRelativeScale3D(FVector(0.07f, 0.07f, 0.07f));

		bRet = true;
	}

	return bRet;
}

void ALightsaberActor::InitialUpdate()
{
	SetBladesColor();
	SetBladesVisibility();
	SetActorHiddenInGame(false);
}

void ALightsaberActor::EnableTrails(bool IsTrailEnabled)
{
	if (IsTrailEnabled && IsEnabled) {
		MainBladeAnimTrail->BeginTrails(Blade1_Trail2, Blade1_Trail1, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.5f);
		if (IsTwoBladed) SecondaryBladeAnimTrail->BeginTrails(Blade2_Trail2, Blade2_Trail1, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.5f);
	}
	else {
		MainBladeAnimTrail->EndTrails();
		SecondaryBladeAnimTrail->EndTrails();
	}
}

void ALightsaberActor::SetBladesVisibility()
{
	if (IsEnabled) {
		if (IsTwoBladed) {
			SaberHandleMesh->SetVisibility(true);
			MainBladeEmitter->SetVisibility(true);
			MainBladeEmitter->Activate();
			MainBladePointLight->SetVisibility(true);
			MainBladeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//MainBladeAnimTrail->BeginTrails(Blade1_Trail1, Blade1_Trail2, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.5f);

			SecondaryBladeEmitter->SetVisibility(true);
			SecondaryBladeEmitter->Activate();
			SecondaryBladePointLight->SetVisibility(true);
			SecondaryBladeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//SecondaryBladeAnimTrail->BeginTrails(Blade2_Trail1, Blade2_Trail2, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.5f);
		}
		else {
			SaberHandleMesh->SetVisibility(true);
			MainBladeEmitter->SetVisibility(true);
			MainBladeEmitter->Activate();
			MainBladePointLight->SetVisibility(true);
			MainBladeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			//MainBladeAnimTrail->BeginTrails(Blade1_Trail1, Blade1_Trail2, ETrailWidthMode::ETrailWidthMode_FromCentre, 1.5f);

			SecondaryBladeEmitter->SetVisibility(false);
			SecondaryBladeEmitter->Deactivate();
			SecondaryBladePointLight->SetVisibility(false);
			SecondaryBladeCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//SecondaryBladeAnimTrail->EndTrails();
		}
	}
	else {
		SaberHandleMesh->SetVisibility(false);
		MainBladeEmitter->SetVisibility(false);
		MainBladeEmitter->Deactivate();
		MainBladePointLight->SetVisibility(false);
		MainBladeCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//MainBladeAnimTrail->EndTrails();

		SecondaryBladeEmitter->SetVisibility(false);
		SecondaryBladeEmitter->Deactivate();
		SecondaryBladePointLight->SetVisibility(false);
		SecondaryBladeCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//SecondaryBladeAnimTrail->EndTrails();
	}
}

void ALightsaberActor::SetBladesColor()
{
	//MainBladeEmitter->SetVectorParameter("SaberColor", FVector(MainBladeColor.R, MainBladeColor.G, MainBladeColor.B));
	MainBladeEmitter->SetColorParameter("SaberColor", MainBladeColor);
	SecondaryBladeEmitter->SetColorParameter("SaberColor", SecondaryBladeColor);
	MainBladePointLight->SetLightColor(MainBladeColor);
	SecondaryBladePointLight->SetLightColor(SecondaryBladeColor);
	MainBladeAnimTrail->SetColorParameter("ParticleColor", MainBladeColor);
	SecondaryBladeAnimTrail->SetColorParameter("ParticleColor", SecondaryBladeColor);
}

void ALightsaberActor::SetSaberEnabled(bool NewEnabled)
{
	IsEnabled = NewEnabled;
	SetBladesVisibility();
}

// Трейсинг по лезвиям для определения точки касания меча с объектом (по типу объекта)
FVector ALightsaberActor::TraceSaberBladeToObject(ECollisionChannel ObjectType, bool IsMain)
{
	FVector vRet;
	FVector vFrom, vTo;
	FCollisionObjectQueryParams CollisionParams;
	FCollisionQueryParams QueryParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), false, this);
	FHitResult RV_Hit(ForceInit);

	vFrom = GetActorLocation();
	if (IsMain)
		vTo = vFrom + SaberHandleMesh->GetUpVector() * SaberLength;
	else
		vTo = vFrom - SaberHandleMesh->GetUpVector() * SaberLength;

	CollisionParams.AddObjectTypesToQuery(ObjectType);
	if (IsValid(OwnerJediCharacter)) QueryParams.AddIgnoredActor(OwnerJediCharacter);
	if (IsValid(FriendlyActor)) QueryParams.AddIgnoredActor(FriendlyActor);

	GetWorld()->LineTraceSingleByObjectType(RV_Hit, vFrom, vTo, CollisionParams, QueryParams);

	if (RV_Hit.bBlockingHit)
		vRet = RV_Hit.ImpactPoint;
	else
		vRet = FVector::ZeroVector;

	return vRet;
}

void ALightsaberActor::SetEmitterLifeSpan(bool IsMain, float LifeSpan)
{
	if (IsMain) {
		MainBurstEmitter->Deactivate();
		MainBurstEmitter->SetEmitterEnable(TEXT("Sparks"), false);
		GetWorldTimerManager().SetTimer(MainEmitterDestroyTimer, this, &ALightsaberActor::OnLifeSpanTimerMain, LifeSpan, false, LifeSpan);
	}
	else {
		SecondaryBurstEmitter->Deactivate();
		SecondaryBurstEmitter->SetEmitterEnable(TEXT("Sparks"), false);
		GetWorldTimerManager().SetTimer(SecondaryEmitterDestroyTimer, this, &ALightsaberActor::OnLifeSpanTimerSecondary, LifeSpan, false, LifeSpan);
	}
}

void ALightsaberActor::OnLifeSpanTimerMain()
{
	MainBurstEmitter->DestroyComponent();
	MainBurstEmitter = nullptr;
	// не нужно на самом деле
	GetWorldTimerManager().ClearTimer(MainEmitterDestroyTimer);
}

void ALightsaberActor::OnLifeSpanTimerSecondary()
{
	SecondaryBurstEmitter->DestroyComponent();
	SecondaryBurstEmitter = nullptr;
	// не нужно на самом деле
	GetWorldTimerManager().ClearTimer(SecondaryEmitterDestroyTimer);
}

void ALightsaberActor::OnBladeBeginOverlap1(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnBladeBeginOverlap(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, true);
}

void ALightsaberActor::OnBladeEndOverlap1(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnBladeEndOverlap(OtherActor, OtherComp, OtherBodyIndex, true);
}

void ALightsaberActor::OnBladeBeginOverlap2(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnBladeBeginOverlap(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult, false);
}

void ALightsaberActor::OnBladeEndOverlap2(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnBladeEndOverlap(OtherActor, OtherComp, OtherBodyIndex, false);
}

void ALightsaberActor::OnBladeBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult, bool IsMain)
{
	if (IsValid(FriendlyActor) && FriendlyActor->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (IsValid(OwnerJediCharacter) && OwnerJediCharacter->GetUniqueID() == OtherActor->GetUniqueID()) return;
	if (!IsInitialized) return;

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("OnBeginOverlap"));
	FVector EmitterLocation = TraceSaberBladeToObject(OtherComp->GetCollisionObjectType(), IsMain);

	if (OtherComp->GetCollisionObjectType() == EEC_LightsaberChannel && !IsValid(PS_SaberCollide)) return;
	if (OtherComp->GetCollisionObjectType() != EEC_LightsaberChannel && !IsValid(PS_WallCollide)) return;
	
	UParticleSystemComponent* NewEmitter;
	if (OtherComp->GetCollisionObjectType() == EEC_LightsaberChannel)
		NewEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_SaberCollide, EmitterLocation, FRotator::ZeroRotator, false);
	else
		NewEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_WallCollide, EmitterLocation, FRotator::ZeroRotator, false);

	if (OtherComp->GetCollisionObjectType() == EEC_LightsaberChannel && IsValid(OwnerJediCharacter))
		OwnerJediCharacter->OnSabersCollided();

	if (IsMain) {
		if (IsValid(MainBurstEmitter))
			MainBurstEmitter->DestroyComponent();
		else
			EmittersCount++;

		MainBurstEmitter = NewEmitter;
		MainBurstEmitterObjectType = OtherComp->GetCollisionObjectType();
	}
	else {
		if (IsValid(SecondaryBurstEmitter))
			SecondaryBurstEmitter->DestroyComponent();
		else
			EmittersCount++;

		SecondaryBurstEmitter = NewEmitter;
		SecondaryBurstEmitterObjectType = OtherComp->GetCollisionObjectType();
	}

	if (OtherComp->GetCollisionObjectType() == EEC_LightsaberChannel && IsValid(OwnerJediCharacter)) {
		if (IsRightHand) {
			OwnerJediCharacter->IK_CollidingRight = true;
			//OwnerJediCharacter->IsSaberAttacking = true;
		}
		else {
			OwnerJediCharacter->IK_CollidingLeft = true;
			//OwnerJediCharacter->IsSaberAttacking = true;
		}
		// если джедай не атакует, задать ему направление
		if (!OwnerJediCharacter->IsSaberAttacking) {
			//AJediCharacter* otherjedi = Cast<AJediCharacter>(OtherActor);
			ALightsaberActor* otherjedisaber = Cast<ALightsaberActor>(OtherActor);

			if (IsValid(otherjedisaber) && IsValid(otherjedisaber->OwnerJediCharacter)) {
				OwnerJediCharacter->SetDirectionKey(otherjedisaber->OwnerJediCharacter->GetDirectionKey());
			}
		}
	}
	
	this->SetActorTickEnabled(true);
}

void ALightsaberActor::OnBladeEndOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool IsMain)
{
	//if (IsValid(FriendlyActor) && FriendlyActor->GetUniqueID() == OtherActor->GetUniqueID()) return;
	//if (IsValid(OwnerJediCharacter) && OwnerJediCharacter->GetUniqueID() == OtherActor->GetUniqueID()) return;

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("OnEndOverlap"));
	if (IsMain && IsValid(MainBurstEmitter)) {
		SetEmitterLifeSpan(true, 0.5f);
	}
	else if (IsValid(SecondaryBurstEmitter)) {
		SetEmitterLifeSpan(false, 0.5f);
	}
	EmittersCount--;

	if (OtherComp->GetCollisionObjectType() == EEC_LightsaberChannel && IsValid(OwnerJediCharacter)) {
		if (IsRightHand)
			OwnerJediCharacter->IK_CollidingRight = false;
		else
			OwnerJediCharacter->IK_CollidingLeft = false;
	}

	if (EmittersCount == 0) this->SetActorTickEnabled(false);
}