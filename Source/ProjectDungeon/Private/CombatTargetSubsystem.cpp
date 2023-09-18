// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDungeon/Public/CombatTargetSubsystem.h"
#include "ProjectDungeon/Public/CombatTargetComponent.h"

void UCombatTargetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

TArray<UCombatTargetComponent*> const& UCombatTargetSubsystem::GetRegisteredTargets() const
{
	return RegisteredTargets;
}

bool UCombatTargetSubsystem::TryRegisterTarget(UCombatTargetComponent* pTargetToRegister)
{
	if (RegisteredTargets.Contains(pTargetToRegister))
	{
		return false;
	}
	
	RegisteredTargets.Add(pTargetToRegister);

	FOnNewTargetRegisteredData eventData;
	eventData.Target = pTargetToRegister;
	
	OnNewTargetRegistered.Broadcast(eventData);
	
	return true;
}

int32 UCombatTargetSubsystem::DeregisterTarget(UCombatTargetComponent* pTargetToDeRegister)
{
	int32 const removedCount = RegisteredTargets.Remove(pTargetToDeRegister);

	FOnTargetDeregisteredData eventData;
	eventData.Target = pTargetToDeRegister;
	
	OnTargetDeregistered.Broadcast(eventData);
	
	return removedCount;
}
