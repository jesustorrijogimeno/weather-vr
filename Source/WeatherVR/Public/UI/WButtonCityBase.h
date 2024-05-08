// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WButtonCityBase.generated.h"

DECLARE_EVENT_OneParam(UWButtonCityBase, FButtonClickedEvent, FString);
/**
 * 
 */
UCLASS()
class WEATHERVR_API UWButtonCityBase : public UUserWidget
{
	GENERATED_BODY()
public:
	FButtonClickedEvent OnButtonClicked;

	UFUNCTION(BlueprintCallable)
	void HandleButtonClick(const FString& CityName);
};
