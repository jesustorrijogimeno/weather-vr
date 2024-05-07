// Fill out your copyright notice in the Description page of Project Settings.


#include "WCitiesSelectorGameMode.h"

#include "Services/WWeatherService.h"

void AWCitiesSelectorGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWWeatherService::FetchCityWeatherStats("London,gb", [](bool a, bool b)
	{
		UE_LOG(LogTemp, Log, TEXT("it works!!!!!!!!!!!!!!!!!!!!!"));
	});
}
