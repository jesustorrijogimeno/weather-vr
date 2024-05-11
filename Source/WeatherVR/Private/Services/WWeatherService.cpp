// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WWeatherService.h"
#include "Services/WServiceCommons.h"
#include "Services/WServiceConstants.h"
#include "Services/Models/FCityStats.h"

void UWWeatherService::FetchCityWeatherStats(const FString& City, TFunction<void(FCityStats)> Callback)
{
    FetchCityCoordinates(City, [Callback](const double& Lat, const double& Lon) {
        FetchCityWeatherStats(Lat, Lon, Callback);
    });
}

void UWWeatherService::FetchCityCoordinates(const FString& City, TFunction<void(double, double)> Callback)
{
    const FString UriBase = FString::Printf(
        TEXT("%s/geo/1.0/direct?q=%s&limit=1&appid=%s"),
        *UWServiceConstants::OPEN_WEATHER_BASE_URL,
        *City,
        *UWServiceConstants::OPEN_WEATHER_KEY);

    UWServiceCommons::UseGet(UriBase, [Callback](const FString& ResponseData)
    {
        ProcessCityCoordinatesResponse(ResponseData, Callback);
    });
}

void UWWeatherService::ProcessCityCoordinatesResponse(const FString& Response, TFunction<void(double, double)> Callback)
{
    const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response);
    TArray<TSharedPtr<FJsonValue>> JsonResponseArray;
    if (!FJsonSerializer::Deserialize(JsonReader, JsonResponseArray))
    {
        return;
    }

    if (JsonResponseArray.Num() != 1)
    {
        UE_LOG(LogTemp, Error, TEXT("City not found"));
        return;
    }

    const TSharedPtr<FJsonObject> JsonObject = JsonResponseArray[0]->AsObject();
    if(!JsonObject)
    {
        return;
    }

    const double Lat = JsonObject->GetNumberField(TEXT("lat"));
    const double Lon = JsonObject->GetNumberField(TEXT("lon"));
    Callback(Lat, Lon);
}

void UWWeatherService::FetchCityWeatherStats(const double Lat, const double Lon, TFunction<void(FCityStats)> Callback)
{
    const FString UriBase = FString::Printf(
        TEXT("%s/data/2.5/weather?lat=%f&lon=%f&appid=%s"),
        *UWServiceConstants::OPEN_WEATHER_BASE_URL,
        Lat,
        Lon,
        *UWServiceConstants::OPEN_WEATHER_KEY);
    
    UWServiceCommons::UseGet(UriBase, [Callback](const FString& ResponseData)
    {
        ProcessCityWeatherStatsResponse(ResponseData, Callback);
    });
}

void UWWeatherService::ProcessCityWeatherStatsResponse(const FString& Response, TFunction<void(FCityStats)> Callback)
{
    const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response);
    TSharedPtr<FJsonObject> JsonObject;
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        return;
    }

    const TArray<TSharedPtr<FJsonValue>> WeatherArray = JsonObject->GetArrayField(TEXT("weather"));
    if (WeatherArray.Num() != 1)
    {
        UE_LOG(LogTemp, Error, TEXT("Weather not found"));
        return;
    }
    
    const TSharedPtr<FJsonObject> WeatherObject = WeatherArray[0]->AsObject();
    const TSharedPtr<FJsonObject> MainObject    = JsonObject->GetObjectField(TEXT("main"));
    const TSharedPtr<FJsonObject> WindObject    = JsonObject->GetObjectField(TEXT("wind"));
    const TSharedPtr<FJsonObject> SysObject    = JsonObject->GetObjectField(TEXT("sys"));
    
    FCityStats CityStats;
    CityStats.Condition             = GetConditionEnum(WeatherObject->GetStringField(TEXT("main")));
    CityStats.ConditionDescription  = WeatherObject->GetStringField(TEXT("description"));
    CityStats.ConditionIcon         = WeatherObject->GetStringField(TEXT("icon"));
    CityStats.Temperature           = MainObject->GetNumberField(TEXT("temp"));
    CityStats.WindSpeed             = WindObject->GetNumberField(TEXT("speed"));
    CityStats.WindDirection         = WindObject->GetNumberField(TEXT("deg"));
    CityStats.TimeZone              = JsonObject->GetNumberField(TEXT("timezone"));
    CityStats.Sunrise               = SysObject->GetNumberField(TEXT("sunrise"));
    CityStats.Sunset                = SysObject->GetNumberField(TEXT("sunset"));
    Callback(CityStats);
}

EWeatherConditions UWWeatherService::GetConditionEnum(const FString& Condition)
{
    static UEnum* Enum = FindFirstObjectSafe<UEnum>(TEXT("EWeatherConditions"));
    if (!Enum)
    {
        return EWeatherConditions::Clear;
    }

    for (int32 i = 0; i < Enum->NumEnums(); ++i)
    {
        FString Name = Enum->GetNameStringByIndex(i);
        if (Name == Condition)
        {
            return static_cast<EWeatherConditions>(Enum->GetValueByIndex(i));
        }
    }
    return EWeatherConditions::Clear;
}