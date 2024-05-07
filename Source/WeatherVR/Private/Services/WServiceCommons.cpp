// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/WServiceCommons.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"

void UWServiceCommons::UseGet(const FString& Uri, TFunction<void(const FString&)> ResponseProcessor)
{
	FHttpModule& HttpModule = FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> const Request = HttpModule.CreateRequest();
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
    Request->SetURL(Uri);
    
    Request->OnProcessRequestComplete().BindLambda(
        [ResponseProcessor](
            const FHttpRequestPtr& HttpRequest,
            const FHttpResponsePtr& HttpResponse,
            const bool bConnectedSuccessfully) mutable {

        if (bConnectedSuccessfully)
        {
            ResponseProcessor(HttpResponse->GetContentAsString());
            return;
        }
        ManageResponseErrors(HttpRequest);
    });
    
    Request->ProcessRequest();
}

void UWServiceCommons::ManageResponseErrors(const FHttpRequestPtr& HttpRequest)
{
    switch (HttpRequest->GetStatus()) {
    case EHttpRequestStatus::Failed_ConnectionError:
        UE_LOG(LogTemp, Error, TEXT("Connection failed."));
    default:
        UE_LOG(LogTemp, Error, TEXT("Request failed."));
    }
}
