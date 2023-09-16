// Fill out your copyright notice in the Description page of Project Settings.


#include "LogUtility.h"

void ULogUtility::AddOnScreenDebugMessageWithObjectContext(UObject* pContextObject, FString const& message, FOnScreenDebugMessageParams params)
{
	GEngine->AddOnScreenDebugMessage(params.Key, params.TimeToDisplay, params.DisplayColor, FString::Printf(TEXT("[%s] %s"), *pContextObject->GetName(), *message));
}
