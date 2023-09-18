// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDungeon/Public/CombatCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "ProjectDungeon/LogUtility.h"
#include "ProjectDungeon/Public/CombatTargetControllerComponent.h"


// Sets default values
ACombatCharacter::ACombatCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController const *pPlayerController = Cast<APlayerController>(Controller);
	if (pPlayerController == nullptr)
	{
		return;
	}
}

// Called every frame
void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ULogUtility::AddOnScreenDebugMessageWithObjectContext(this, FString::Printf(TEXT("Character World Location: %s"), *this->GetActorLocation().ToString()));
}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACombatCharacter::Move(FVector2D const &movementVector)
{
	if (Controller == nullptr)
	{
		return;
	}

	FRotator const rotation = Controller->GetControlRotation();
	FRotator const yRotation = FRotator(0, rotation.Yaw, 0);

	FVector const forward = FRotationMatrix(yRotation).GetUnitAxis(EAxis::X);
	FVector const right = FRotationMatrix(yRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(forward, movementVector.Y);
	AddMovementInput(right, movementVector.X);
}

void ACombatCharacter::RotateCamera(FVector2D lookAxisVector)
{
	// add yaw and pitch input to controller
	AddControllerYawInput(lookAxisVector.X);
	AddControllerPitchInput(lookAxisVector.Y);
}


