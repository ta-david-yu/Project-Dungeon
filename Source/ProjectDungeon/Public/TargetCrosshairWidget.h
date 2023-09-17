// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTDUNGEON_API UTargetCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UCombatTargetComponent *m_pTarget = nullptr;
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable)
	class UCombatTargetComponent *GetCombatTarget() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCombatTarget(class UCombatTargetComponent *pCombatTargetComponent);
};
