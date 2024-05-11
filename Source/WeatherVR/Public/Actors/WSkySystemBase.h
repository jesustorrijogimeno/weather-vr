// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/WUpdateEnvironment.h"
#include "WSkySystemBase.generated.h"

UCLASS()
class WEATHERVR_API AWSkySystemBase : public AActor, public IWUpdateEnvironment
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWSkySystemBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float TimeOfDay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float Sunrise;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float Sunset;
	
	virtual void Update_Implementation(FCityStats CityStats) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ConfigureDynamicSky();
};
