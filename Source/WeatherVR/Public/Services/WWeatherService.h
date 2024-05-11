// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/EWeatherConditions.h"
#include "WWeatherService.generated.h"

struct FCityStats;
/**
 * 
 */
UCLASS()
class WEATHERVR_API UWWeatherService : public UObject
{
	GENERATED_BODY()

public:
	static void FetchCityWeatherStats(const FString& City, TFunction<void(FCityStats)> Callback);
	static void FetchCityWeatherStats(const double Lat, const double Lon, TFunction<void(FCityStats)> Callback);
	static void FetchCityCoordinates(const FString& City, TFunction<void(double, double)> Callback);
protected:
	static void ProcessCityCoordinatesResponse(const FString& Response, TFunction<void(double, double)> Callback);
	static void ProcessCityWeatherStatsResponse(const FString& Response, TFunction<void(FCityStats)> Callback);
	static EWeatherConditions GetConditionEnum(const FString& Condition);
};
