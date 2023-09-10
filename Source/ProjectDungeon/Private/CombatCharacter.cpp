// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDungeon/Private/CombatCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACombatCharacter::ACombatCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pPlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

// Called every frame
void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, FString::Printf(TEXT("Character World Location: %s"), *this->GetActorLocation().ToString()));
}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent *pInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (pInputComponent == nullptr)
	{
		return;
	}
	
	pInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACombatCharacter::handleMoveInput);
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

void ACombatCharacter::handleMoveInput(FInputActionValue const& Value)
{
	if (Controller == nullptr)
	{
		return;
	}

	auto vector = Value.Get<FVector2D>();
	Move(vector);
}


