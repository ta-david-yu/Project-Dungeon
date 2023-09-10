// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

ACombatPlayerController::ACombatPlayerController()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void ACombatPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto *pPawn = GetPawnOrSpectator();
	if (pPawn)
	{
		GetRootComponent()->SetWorldLocation(pPawn->GetActorLocation());
		//CameraBoom->SetWorldLocation(pPawn->GetActorLocation());	
	}

	auto *pViewTarget = this->GetViewTarget();
	
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("Controller Camera World Location: %s"), *FollowCamera->GetComponentLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("View Target (%s) World Location: %s"), *pViewTarget->GetName(), *pViewTarget->GetActorLocation().ToString()));
}

void ACombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent *pInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (pInputComponent == nullptr)
	{
		return;
	}
	
	pInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACombatPlayerController::handleLookInputAction);
}

void ACombatPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//this->SetViewTarget(this);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Possess %s"), *InPawn->GetName()));
}

void ACombatPlayerController::RotateCamera(FVector2D lookAxisVector)
{
	this->AddYawInput(lookAxisVector.X);
	this->AddPitchInput(lookAxisVector.Y);
}

void ACombatPlayerController::handleLookInputAction(FInputActionValue const& value)
{
	FVector2D lookAxisVector = value.Get<FVector2D>();
	RotateCamera(lookAxisVector);
}
