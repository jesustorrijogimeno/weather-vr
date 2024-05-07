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
	int32 CurrentTime;

	FCityStats()
	{
		Condition = EWeatherConditions::Clear;
		Temperature = 0;
		WindDirection = 0;
		WindSpeed = 0;
		CurrentTime = 0;
	}
};
