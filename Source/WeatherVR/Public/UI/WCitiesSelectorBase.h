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
	TObjectPtr<UTextBlock> CityTextBlock;
	UPROPERTY()
	TObjectPtr<UTextBlock> TemperatureTextBlock;
	UPROPERTY()
	TObjectPtr<UTextBlock> ConditionTextBlock;
	UPROPERTY()
	TObjectPtr<UTextBlock> WindDirectionTextBlock;
	UPROPERTY()
	TObjectPtr<UTextBlock> WindSpeedTextBlock;
	UPROPERTY()
	TObjectPtr<UTextBlock> CurrentTimeTextBlock;
	void FillInCityStatsWidget(const FCityStats& CityStats) const;
};
