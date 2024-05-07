// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WWeatherService.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Services/WServiceConstants.h"

void UWWeatherService::FetchCityWeatherStats(const FString& City, TFunction<void(bool, bool)> Callback)
{
    FetchCityCoordinates(City, [Callback](const double& Lat, const double& Lon) {
        FetchCityWeatherStats(Lat, Lon, Callback);
    });
}

void UWWeatherService::FetchCityCoordinates(const FString& City, TFunction<void(double, double)> Callback)
{
    //London,gb
    const FString UriBase = FString::Printf(
        TEXT("%s/geo/1.0/direct?q=%s&limit=1&appid=%s"),
        *UWServiceConstants::OPEN_WEATHER_BASE_URL,
        *City,
        *UWServiceConstants::OPEN_WEATHER_KEY);
    
    FHttpModule& HttpModule = FHttpModule::Get();
    
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const Request = HttpModule.CreateRequest();
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    Request->SetURL(UriBase);
    
    Request->OnProcessRequestComplete().BindLambda(
        [Callback](
            const FHttpRequestPtr& HttpRequest,
            const FHttpResponsePtr& HttpResponse,
            const bool bConnectedSuccessfully) mutable {

        if (bConnectedSuccessfully) {
            ProcessCityCoordinatesResponse(HttpResponse->GetContentAsString(), Callback);
            return;
        }
            
        switch (HttpRequest->GetStatus()) {
        case EHttpRequestStatus::Failed_ConnectionError:
            UE_LOG(LogTemp, Error, TEXT("Connection failed."));
        default:
            UE_LOG(LogTemp, Error, TEXT("Request failed."));
        }
    });
    
    Request->ProcessRequest();
}

void UWWeatherService::ProcessCityCoordinatesResponse(const FString& Response, TFunction<void(double, double)> Callback)
{
    UE_LOG(LogTemp, Error, TEXT("%s"), *Response);
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
    UE_LOG(LogTemp, Log, TEXT("City Lat %f - Lon %f"), Lat, Lon);
}

void UWWeatherService::FetchCityWeatherStats(const double Lat, const double Lon, TFunction<void(bool, bool)> Callback)
{
    const FString UriBase = FString::Printf(
        TEXT("%s/data/2.5/weather?lat=%f&lon=%f&appid=%s"),
        *UWServiceConstants::OPEN_WEATHER_BASE_URL,
        Lat,
        Lon,
        *UWServiceConstants::OPEN_WEATHER_KEY);
    
    FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const Request = HttpModule.CreateRequest();
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    Request->SetURL(UriBase);
    
    Request->OnProcessRequestComplete().BindLambda(
        [Callback](
            const FHttpRequestPtr& HttpRequest,
            const FHttpResponsePtr& HttpResponse,
            const bool bConnectedSuccessfully) mutable {

        if (bConnectedSuccessfully) {
            ProcessCityWeatherStatsResponse(HttpResponse->GetContentAsString(), Callback);
            return;
        }
            
        switch (HttpRequest->GetStatus()) {
        case EHttpRequestStatus::Failed_ConnectionError:
            UE_LOG(LogTemp, Error, TEXT("Connection failed."));
        default:
            UE_LOG(LogTemp, Error, TEXT("Request failed."));
        }
    });
    
    Request->ProcessRequest();
}

void UWWeatherService::ProcessCityWeatherStatsResponse(const FString& Response, TFunction<void(bool, bool)> Callback)
{
    UE_LOG(LogTemp, Log, TEXT("%s"), *Response);
}