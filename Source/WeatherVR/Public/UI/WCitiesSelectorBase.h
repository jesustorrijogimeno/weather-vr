// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
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
	void SubscribeButtons(UVerticalBox* VerticalBox);
};
