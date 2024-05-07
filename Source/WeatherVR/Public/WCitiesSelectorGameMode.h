// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WCitiesSelectorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WEATHERVR_API AWCitiesSelectorGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
