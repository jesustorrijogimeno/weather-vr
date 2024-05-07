// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WServiceConstants.generated.h"

/**
 * 
 */
UCLASS()
class WEATHERVR_API UWServiceConstants : public UObject
{
	GENERATED_BODY()
public:
	inline static const FString OPEN_WEATHER_KEY = "1339f3c529270d7d40a70197935f4b35";
	inline static const FString OPEN_WEATHER_BASE_URL = "https://api.openweathermap.org";
	
};
