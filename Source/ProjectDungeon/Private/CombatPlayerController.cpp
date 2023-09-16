// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectDungeon/LogUtility.h"

ACombatPlayerController::ACombatPlayerController()
{
}

void ACombatPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto *pViewTarget = this->GetViewTarget();
	ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, FString::Printf(TEXT("Character World Location: %s"), *pViewTarget->GetName(), *pViewTarget->GetActorLocation().ToString()));
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ACombatPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//this->SetViewTarget(this);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Possess %s"), *InPawn->GetName()));
}
