// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WSkySystemBase.h"

// Sets default values
AWSkySystemBase::AWSkySystemBase()
{
	TimeOfDay = 9;
	Sunrise = 6;
	Sunset = 18;
	WeatherCondition = EWeatherConditions::Clear;
}

void AWSkySystemBase::Update_Implementation(const FCityStats CityStats)
{
	TimeOfDay			= CityStats.Time.GetHour() + CityStats.Time.GetMinute() / 60.0f;
	Sunrise				= CityStats.SunriseTime.GetHour() + CityStats.SunriseTime.GetMinute() / 60.0f;
	Sunset				= CityStats.SunsetTime.GetHour() + CityStats.SunsetTime.GetMinute() / 60.0f;
	WeatherCondition	= CityStats.Condition;
	ConfigureDynamicSky();
}

