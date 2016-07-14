// Fill out your copyright notice in the Description page of Project Settings.

#include "JA_Character.h"
#include "AIPathFollowingComponent.h"
#include "AIAdvancedController.h"


AAIAdvancedController::AAIAdvancedController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAIPathFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

