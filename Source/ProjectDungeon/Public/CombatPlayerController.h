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
public:
	ACombatPlayerController();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
};
