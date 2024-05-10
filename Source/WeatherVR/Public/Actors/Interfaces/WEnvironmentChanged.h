// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Models/FCityStats.h"
#include "UObject/Interface.h"
#include "WEnvironmentChanged.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWEnvironmentChanged : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WEATHERVR_API IWEnvironmentChanged
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateEnvironment(FCityStats CityStats);
};
