// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WCitiesSelectorBase.h"

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
	this->CityTextBlock				= CityTextBlock;
	this->TemperatureTextBlock		= TemperatureTextBlock;
	this->ConditionTextBlock		= ConditionTextBlock;
	this->WindDirectionTextBlock	= WindDirectionTextBlock;
	this->WindSpeedTextBlock		= WindSpeedTextBlock;
	this->CurrentTimeTextBlock		= CurrentTimeTextBlock;
	for (int32 i = 0; i < VerticalBox->GetChildrenCount(); ++i)
	{
		UWidget* ChildWidget = VerticalBox->GetChildAt(i);
		if (ChildWidget->IsA<UWButtonCityBase>())
		{
			UWButtonCityBase* Button = Cast<UWButtonCityBase>(ChildWidget);
			Button->OnButtonClicked.AddLambda(
				[this](const FString& CityName)
					{
						this->CityName = CityName;
						UWWeatherService::FetchCityWeatherStats(CityName, this->FillInCityStatsWidget);
					});
		}
	}
}

void UWCitiesSelectorBase::FillInCityStatsWidget(const FCityStats& CityStats) const
{
	this->CityTextBlock->SetText(FText::FromString(this->CityName));
	this->TemperatureTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%f F"), CityStats.Temperature)));
	this->ConditionTextBlock->SetText(FText::FromString(CityStats.ConditionDescription));
	this->WindDirectionTextBlock->SetText(FText::AsNumber(CityStats.WindDirection));
	this->WindSpeedTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%f m/s"), CityStats.WindSpeed)));
	this->CurrentTimeTextBlock->SetText(FText::AsDateTime(FDateTime::FromUnixTimestamp(CityStats.CurrentTime)));
}
