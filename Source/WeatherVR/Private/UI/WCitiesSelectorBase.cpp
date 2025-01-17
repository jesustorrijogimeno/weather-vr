// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WCitiesSelectorBase.h"
#include "Actors/Interfaces/WUpdateEnvironment.h"
#include "Services/WWeatherService.h"
#include "Services/Models/FCityStats.h"
#include "UI/WButtonCityBase.h"

void UWCitiesSelectorBase::SubscribeButtons(
	UVerticalBox* VerticalBox,
	UTextBlock* CityTextBlock,
	UTextBlock* TemperatureTextBlock,
	UTextBlock* ConditionTextBlock,
	UTextBlock* WindDirectionTextBlock,
	UTextBlock* WindSpeedTextBlock,
	UTextBlock* CurrentTimeTextBlock
)
{
	this->CityTextBlockProp				= CityTextBlock;
	this->TemperatureTextBlockProp		= TemperatureTextBlock;
	this->ConditionTextBlockProp		= ConditionTextBlock;
	this->WindDirectionTextBlockProp	= WindDirectionTextBlock;
	this->WindSpeedTextBlockProp		= WindSpeedTextBlock;
	this->CurrentTimeTextBlockProp		= CurrentTimeTextBlock;
	for (int32 i = 0; i < VerticalBox->GetChildrenCount(); ++i)
	{
		UWidget* ChildWidget = VerticalBox->GetChildAt(i);
		if (!ChildWidget->IsA<UWButtonCityBase>())
		{
			continue;
		}
		
		UWButtonCityBase* Button = Cast<UWButtonCityBase>(ChildWidget);
		Button->OnButtonClicked.AddLambda(
			[this](const FString& CityName)
				{
					this->CityName = CityName;
					UWWeatherService::FetchCityWeatherStats(CityName, [this](FCityStats CityStats)
					{
						FillInCityStatsWidget(CityStats);
						for(TObjectIterator<UObject> Object; Object; ++Object)
						{
							if (!Object->Implements<UWUpdateEnvironment>()) continue;
							const IWUpdateEnvironment* EnvironmentChanged = Cast<IWUpdateEnvironment>(*Object);
							EnvironmentChanged->Execute_Update(*Object, CityStats);
						}
					});
				});
	}
}

void UWCitiesSelectorBase::FillInCityStatsWidget(FCityStats& CityStats) const
{
	this->CityTextBlockProp->SetText(FText::FromString(this->CityName));
	this->TemperatureTextBlockProp->SetText(FText::FromString(FString::Printf(TEXT("%.2f F"), RoundFloat(CityStats.Temperature))));
	this->ConditionTextBlockProp->SetText(FText::FromString(CityStats.ConditionDescription));
	this->WindDirectionTextBlockProp->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), RoundFloat(CityStats.WindDirection))));
	this->WindSpeedTextBlockProp->SetText(FText::FromString(FString::Printf(TEXT("%.2f m/s"), RoundFloat(CityStats.WindSpeed))));
	const FDateTime CurrentDate = FDateTime::UtcNow() + FTimespan(0, 0, CityStats.TimeZone);
	this->CurrentTimeTextBlockProp->SetText(FText::FromString(CurrentDate.ToString()));
	CityStats.Time = CurrentDate;
	CityStats.SunriseTime	= FDateTime::FromUnixTimestamp(CityStats.Sunrise) + FTimespan(0, 0, CityStats.TimeZone);
	CityStats.SunsetTime	= FDateTime::FromUnixTimestamp(CityStats.Sunset) + FTimespan(0, 0, CityStats.TimeZone);
}

float UWCitiesSelectorBase::RoundFloat(const float FloatToRound)
{
	const int RoundToInt =  FMath::RoundToZero(FloatToRound * 100);
	return RoundToInt / 100.0f;
}