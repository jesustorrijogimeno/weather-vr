// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Services/Models/FCityStats.h"
#include "WCitiesSelectorBase.generated.h"

class UWButtonCityBase;

/**
 * 
 */
UCLASS()
class WEATHERVR_API UWCitiesSelectorBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SubscribeButtons(
		UVerticalBox* VerticalBox,
		UTextBlock* CityTextBlock,
		UTextBlock* TemperatureTextBlock,
		UTextBlock* ConditionTextBlock,
		UTextBlock* WindDirectionTextBlock,
		UTextBlock* WindSpeedTextBlock,
		UTextBlock* CurrentTimeTextBlock
	);
protected:
	FString CityName;
	UPROPERTY()
	TObjectPtr<UTextBlock> CityTextBlockProp;
	UPROPERTY()
	TObjectPtr<UTextBlock> TemperatureTextBlockProp;
	UPROPERTY()
	TObjectPtr<UTextBlock> ConditionTextBlockProp;
	UPROPERTY()
	TObjectPtr<UTextBlock> WindDirectionTextBlockProp;
	UPROPERTY()
	TObjectPtr<UTextBlock> WindSpeedTextBlockProp;
	UPROPERTY()
	TObjectPtr<UTextBlock> CurrentTimeTextBlockProp;
	void FillInCityStatsWidget(const FCityStats& CityStats) const;
	static float RoundFloat(float FloatToRound);
};
