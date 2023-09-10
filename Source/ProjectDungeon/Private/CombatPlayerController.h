// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CombatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDUNGEON_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TexCreate_InputAttachmentRead, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;
	
public:
	ACombatPlayerController();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	void RotateCamera(FVector2D lookAxisVector);

private:
	void handleLookInputAction(FInputActionValue const& value);
};
