// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDungeon/Public/CombatTargetComponent.h"

#include "Logging/StructuredLog.h"
#include "ProjectDungeon/Public/CombatTargetSubsystem.h"


// Sets default values for this component's properties
UCombatTargetComponent::UCombatTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	bool const result = GetWorld()->GetSubsystem<UCombatTargetSubsystem>()->TryRegisterTarget(this);
	if (!result)
	{
		UE_LOGFMT(LogTemp, Warning, "Failed to register target '%s'", *GetName());
	}
}

void UCombatTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetSubsystem<UCombatTargetSubsystem>()->DeregisterTarget(this);
	
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UCombatTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USceneComponent* UCombatTargetComponent::GetCrosshairAnchor() const
{
	if (m_pCrosshairAnchor)
	{
		return m_pCrosshairAnchor;
	}

	return GetOwner()->GetRootComponent();
}

