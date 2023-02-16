// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MyBlueprintFunctionLibrary.h"

void UMyGameInstance::Init()
{
	Super::Init();

	FTickerDelegate TickDelegate = FTickerDelegate::CreateUObject(this, &UMyGameInstance::Tick);
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

	FCoreDelegates::OnControllerConnectionChange.AddUObject(this, &UMyGameInstance::HandleControllerConnectionChange);
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

bool UMyGameInstance::Tick(float DeltaTime)
{
	if (GEngine)
	{
		FString message = FString::Printf(TEXT("Active Controller ID: %d"), ActiveControllerId);

		GEngine->AddOnScreenDebugMessage(1, 0.2f, FColor::Blue, *message);
	}

	return true;
}

void UMyGameInstance::SetActiveControllerID(int32 ControllerID)
{
	ActiveControllerId = ControllerID;
}

int32 UMyGameInstance::GetActiveControllerID()
{
	return ActiveControllerId;
}

void UMyGameInstance::HandleControllerConnectionChange(bool bConnected, FPlatformUserId UserId, int32 ControllerId)
{
	FString UserId_Text;
	if (UserId == PLATFORMUSERID_NONE)
	{
		UserId_Text = TEXT("None");
	}
	else
	{
		UserId_Text = FString::Printf(TEXT("%d"), UserId.GetInternalId());
	}

	FString message = FString::Printf(TEXT("Controller connection changed - UserIdx:%d, UserID:%s, Connected:%d"), ControllerId, *UserId_Text, bConnected ? 1 : 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *message);

	if (GetActiveControllerID() == ControllerId)
	{
		if (APlayerController* ActivePC = UMyBlueprintFunctionLibrary::GetActivePlayerController(this))
		{
			if (bConnected) // Our active controller connected
			{
				if (bDidContronllerDisconnectPauseGame)
				{
					UGameplayStatics::SetGamePaused(this, false);
					bDidContronllerDisconnectPauseGame = false;
				}
				if (ControllerDisconnectedWidget)
				{
					ControllerDisconnectedWidget->RemoveFromParent();
				}
			}
			else // Our active controller disconnected
			{
				if (ControllerDisconnectedWidgetClass)
				{
					if (!UGameplayStatics::IsGamePaused(this))
					{
						bDidContronllerDisconnectPauseGame = true;
						UGameplayStatics::SetGamePaused(this, true);
					}
					ControllerDisconnectedWidget = CreateWidget<UControllerDisconnectedWidget>(ActivePC, ControllerDisconnectedWidgetClass);
					ControllerDisconnectedWidget->AddToViewport();
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ControllerDisconnectedWidgetClass NOT set!"));
				}
			}
		}
	}
}

