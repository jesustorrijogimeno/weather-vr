// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WCitiesSelectorBase.h"
#include "UI/WButtonCityBase.h"

void UWCitiesSelectorBase::SubscribeButtons(UVerticalBox* VerticalBox)
{
	for (int32 i = 0; i < VerticalBox->GetChildrenCount(); ++i)
	{
		UWidget* ChildWidget = VerticalBox->GetChildAt(i);
		if (ChildWidget->IsA<UWButtonCityBase>())
		{
			UWButtonCityBase* Button = Cast<UWButtonCityBase>(ChildWidget);
			Button->OnButtonClicked.AddLambda([](const FString& CityName)
			{
				UE_LOG(LogTemp, Warning, TEXT("Name Clicked -> %s"), *CityName);
			});
		}
	}
}
