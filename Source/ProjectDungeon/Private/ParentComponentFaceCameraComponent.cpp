// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentComponentFaceCameraComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UParentComponentFaceCameraComponent::UParentComponentFaceCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParentComponentFaceCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UParentComponentFaceCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	auto *parent = GetAttachParent();
	if (parent == nullptr)
	{
		return;
	}
	
	APlayerCameraManager const *cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), TargetCameraPlayerIndex);
	if (cameraManager == nullptr)
	{
		return;
	}
	
	auto const location = parent->GetComponentLocation();
	auto const cameraLocation = cameraManager->GetCameraLocation();

	FRotator lookRotation = UKismetMathLibrary::FindLookAtRotation(location, cameraLocation);
	lookRotation.Roll = 0;
	
	parent->SetWorldRotation(lookRotation);
}

