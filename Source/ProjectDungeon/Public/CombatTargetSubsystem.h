// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Containers/Array.h"

#include "CombatTargetSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FOnNewTargetRegisteredData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatTargetComponent *Target;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewTargetRegistered, FOnNewTargetRegisteredData, data);


USTRUCT(BlueprintType)
struct FOnTargetDeregisteredData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatTargetComponent *Target;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDeregistered, FOnTargetDeregisteredData, data);

/**
 * 
 */
UCLASS()
class PROJECTDUNGEON_API UCombatTargetSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class UCombatTargetComponent*> RegisteredTargets;

public:
	UPROPERTY(BlueprintAssignable)
	FOnNewTargetRegistered OnNewTargetRegistered;
	
	UPROPERTY(BlueprintAssignable)
	FOnTargetDeregistered OnTargetDeregistered;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	TArray<class UCombatTargetComponent*> const& GetRegisteredTargets() const;
	
	/// @return Whether or not the target has been successfully registered.
	bool TryRegisterTarget(UCombatTargetComponent *pTargetToRegister);

	/// @return the number of deregistered targets.
	int32 DeregisterTarget(UCombatTargetComponent *pTargetToDeRegister);

	template<class Func>
	void ForEachTargetWithIndex(Func func)
	{
		for (int i = 0; i < RegisteredTargets.Num(); i++)
		{
			auto target = RegisteredTargets[i];
			func(target, i);
		}
	}
	
	template<class Func>
	void ForEachTargetWithIndex(Func func) const
	{
		for (int i = 0; i < RegisteredTargets.Num(); i++)
		{
			auto target = RegisteredTargets[i];
			func(target, i);
		}
	}
};
