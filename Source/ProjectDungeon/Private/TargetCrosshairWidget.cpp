// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetCrosshairWidget.h"

void UTargetCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

UCombatTargetComponent* UTargetCrosshairWidget::GetCombatTarget() const
{
	return m_pTarget;
}

void UTargetCrosshairWidget::SetCombatTarget(UCombatTargetComponent* pCombatTargetComponent)
{
	m_pTarget = pCombatTargetComponent;
}
