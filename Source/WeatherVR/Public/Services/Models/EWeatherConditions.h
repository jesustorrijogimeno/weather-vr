// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EWeatherConditions.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EWeatherConditions : uint8
{
	Clear UMETA(DisplayName="Clear"),
	Rain UMETA(DisplayName="Rain"),
	Clouds UMETA(DisplayName="Clouds"),
	Thunderstorm UMETA(DisplayName="Thunderstorm"),
	Drizzle UMETA(DisplayName="Drizzle"),
	Snow UMETA(DisplayName="Snow")
};
