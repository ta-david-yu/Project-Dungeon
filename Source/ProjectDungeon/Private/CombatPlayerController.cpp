// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"

#include "Components/InputComponent.h"
#include "ProjectDungeon/LogUtility.h"

ACombatPlayerController::ACombatPlayerController()
{
}

void ACombatPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto const *pViewTarget = this->GetViewTarget();
	ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, FString::Printf(TEXT("Character World Location: %s"), *pViewTarget->GetActorLocation().ToString()));
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ACombatPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
