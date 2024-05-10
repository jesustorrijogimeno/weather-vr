// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EWeatherConditions.h"
#include "FCityStats.generated.h"

enum class EWeatherConditions : uint8;

USTRUCT(BlueprintType)
struct FCityStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Temperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeatherConditions Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ConditionDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ConditionIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WindDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WindSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 TimeZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Sunrise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Sunset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime SunriseTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime SunsetTime;

	FCityStats()
	{
		Condition = EWeatherConditions::Clear;
		Temperature = 0;
		WindDirection = 0;
		WindSpeed = 0;
		TimeZone = 0;
		Sunrise = 0;
		Sunset = 0;
	}
};
