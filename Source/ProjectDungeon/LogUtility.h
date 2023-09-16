// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogUtility.generated.h"

USTRUCT(BlueprintType)
struct FOnScreenDebugMessageParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Key = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToDisplay = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor DisplayColor = FColor::White;
};	


UCLASS()
class PROJECTDUNGEON_API ULogUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Log, meta=(DefaultToSelf="pContextObject"))
	static void AddOnScreenDebugMessageWithObjectContext(UObject* pContextObject, FString const& message, FOnScreenDebugMessageParams params = FOnScreenDebugMessageParams());
};
