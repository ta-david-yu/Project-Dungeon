// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Containers/Array.h"

#include "CombatTargetSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDUNGEON_API UCombatTargetSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class UCombatTargetComponent*> m_RegisteredTargets;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/// @return Whether or not the target has been successfully registered.
	bool TryRegisterTarget(UCombatTargetComponent *pTargetToRegister);

	/// @return the number of deregistered targets.
	int32 DeregisterTarget(UCombatTargetComponent *pTargetToDeRegister);
};
