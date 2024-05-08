// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WButtonCityBase.h"

void UWButtonCityBase::HandleButtonClick(const FString& CityName)
{
	OnButtonClicked.Broadcast(CityName);
}
