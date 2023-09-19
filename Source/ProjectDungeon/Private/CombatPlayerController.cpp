// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"

#include "CombatCharacter.h"
#include "CombatTargetComponent.h"
#include "CombatTargetControllerComponent.h"
#include "CombatTargetSubsystem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Logging/StructuredLog.h"
#include "ProjectDungeon/LogUtility.h"

ACombatPlayerController::ACombatPlayerController()
{
}

void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
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

	UEnhancedInputComponent *enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (enhancedInputComponent == nullptr)
	{
		return;
	}
	
	enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACombatPlayerController::handleMoveInput);
	enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACombatPlayerController::handleLookInput);
	enhancedInputComponent->BindAction(AutoLockTargetAction, ETriggerEvent::Started, this, &ACombatPlayerController::handleAutoLockTargetInput);
}

void ACombatPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCombatCharacter = CastChecked<ACombatCharacter>(InPawn);
	if (PossessedCombatCharacter == nullptr)
	{
		UE_LOGFMT(LogTemp, Log, "The possessed pawn is not a combat character, it will not be moved by the player controller.");
		FOnScreenDebugMessageParams params;
		params.TimeToDisplay = 5;
		ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, "The possessed pawn is not a combat character, it will not be moved by the player controller.", params);
	}
}

void ACombatPlayerController::AutoLockTargetClosestToViewCenter()
{
	UCombatTargetComponent *bestCandidateTarget = TryGetTargetClosestToViewCenter();

	CurrentTarget = bestCandidateTarget;

	FOnScreenDebugMessageParams params;
	params.TimeToDisplay = 3.0f;

	if (CurrentTarget != nullptr)
	{
		ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, FString::Printf(TEXT("New target: %s"), *CurrentTarget->GetOwner()->GetActorNameOrLabel()), params);	
	}
	else
	{
		ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, FString::Printf(TEXT("No target")), params);
	}
}

UCombatTargetComponent* ACombatPlayerController::TryGetTargetClosestToViewCenter() const
{
	auto const cameraLocation = PlayerCameraManager->GetCameraLocation();
	auto cameraLookVector = PlayerCameraManager->GetCameraRotation().Vector();
	cameraLookVector.Z = 0;
	
	UCombatTargetSubsystem const* combatTargetSubsystem = GetWorld()->GetSubsystem<UCombatTargetSubsystem>();
	auto const allTargets = combatTargetSubsystem->GetRegisteredTargets();

	UCombatTargetComponent *bestCandidateTarget = nullptr;
	double smallestAngleInRadian = TNumericLimits<double>::Max();
	double smallestSqrDistance = TNumericLimits<double>::Max();
	for (int32 i = 0; i < allTargets.Num(); i++)
	{
		UCombatTargetComponent *target = allTargets[i];
		bool const isOnScreen = target->GetCrosshairAnchor()->GetOwner()->WasRecentlyRendered();
		if (!isOnScreen)
		{
			continue;
		}
		
		auto const targetLocation = target->GetCrosshairAnchor()->GetComponentLocation();
		FVector cameraToTarget = targetLocation - cameraLocation;
		cameraToTarget.Z = 0;
		double const sqrDistance = cameraToTarget.SquaredLength();
		
		FVector nAxis;
		float angleInRadian = 0.0f;
		FQuat betweenQuat = FQuat::FindBetweenVectors(cameraToTarget, cameraLookVector);
		betweenQuat.ToAxisAndAngle(nAxis, angleInRadian);
		
		bool isNewCandidate = false;
		//double const angleTolerance = FMath::DegreesToRadians(1.0f);
		if (FMath::IsNearlyEqual(angleInRadian, smallestAngleInRadian))
		{
			if (sqrDistance < smallestSqrDistance)
			{
				isNewCandidate = true;
			}
		}
		else if (angleInRadian < smallestAngleInRadian)
		{
			isNewCandidate = true;
		}

		if (isNewCandidate)
		{
			bestCandidateTarget = target;
			smallestAngleInRadian = angleInRadian;
			smallestSqrDistance = sqrDistance;
		}
		
		DrawDebugString(GetWorld(), targetLocation, FString::Printf(TEXT("Angle: %f, SqrDistance: %f"), angleInRadian, sqrDistance), nullptr, FColor::White, 0, false, 2);
	}

	return bestCandidateTarget;
}

void ACombatPlayerController::handleMoveInput(FInputActionValue const& Value)
{
	if (PossessedCombatCharacter == nullptr)
	{
		return;
	}

	FVector2D const vector = Value.Get<FVector2D>();
	PossessedCombatCharacter->Move(vector);
}

void ACombatPlayerController::handleLookInput(FInputActionValue const& value)
{
	if (PossessedCombatCharacter == nullptr)
	{
		return;
	}
	
	FVector2D const lookAxisVector = value.Get<FVector2D>();
	PossessedCombatCharacter->RotateCamera(lookAxisVector);
}

void ACombatPlayerController::handleAutoLockTargetInput()
{
	AutoLockTargetClosestToViewCenter();
}
