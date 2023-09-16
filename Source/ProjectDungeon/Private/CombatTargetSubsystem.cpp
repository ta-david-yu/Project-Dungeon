// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDungeon/Public/CombatTargetSubsystem.h"
#include "ProjectDungeon/Public/CombatTargetComponent.h"

void UCombatTargetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

bool UCombatTargetSubsystem::TryRegisterTarget(UCombatTargetComponent* pTargetToRegister)
{
	if (m_RegisteredTargets.Contains(pTargetToRegister))
	{
		return false;
	}
	
	m_RegisteredTargets.Add(pTargetToRegister);
	return true;
}

int32 UCombatTargetSubsystem::DeregisterTarget(UCombatTargetComponent* pTargetToDeRegister)
{
	return m_RegisteredTargets.Remove(pTargetToDeRegister);
}
