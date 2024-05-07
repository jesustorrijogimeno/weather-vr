// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "WServiceCommons.generated.h"

/**
 * 
 */
UCLASS()
class WEATHERVR_API UWServiceCommons : public UObject
{
	GENERATED_BODY()
public:
	static void UseGet(const FString& Uri, TFunction<void(const FString&)> ResponseProcessor);
	static void ManageResponseErrors(const FHttpRequestPtr& HttpRequest );
};
