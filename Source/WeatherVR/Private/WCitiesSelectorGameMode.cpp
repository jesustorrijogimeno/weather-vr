// Fill out your copyright notice in the Description page of Project Settings.


#include "WCitiesSelectorGameMode.h"

#include "Services/WWeatherService.h"
#include "Services/Models/FCityStats.h"

void AWCitiesSelectorGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWWeatherService::FetchCityWeatherStats("London,gb", [](FCityStats CityStats)
	{
		UE_LOG(LogTemp, Log, TEXT("it works!!!!!!! %s"), *CityStats.ConditionDescription);
	});
}
