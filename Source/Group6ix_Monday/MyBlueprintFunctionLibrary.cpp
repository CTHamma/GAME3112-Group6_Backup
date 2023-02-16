// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

int32 UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex()
{
	return UMyGameInstance::MAX_CONTROLLERS - 1;
}

void UMyBlueprintFunctionLibrary::SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		GameInstanceRef->SetActiveControllerID(ControllerID);
	}
}

int32 UMyBlueprintFunctionLibrary::GetActiveControllerID(const UObject* WorldContextObject)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		return GameInstanceRef->GetActiveControllerID();
	}
	return -1;
}

void UMyBlueprintFunctionLibrary::RemoveAllPlayers(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerController::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		APlayerController* PC = Cast<APlayerController>(Actor);
		if (PC)
		{
			UGameplayStatics::RemovePlayer(PC, true);
		}
	}
}

APlayerController* UMyBlueprintFunctionLibrary::GetActivePlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, GetActiveControllerID(WorldContextObject));
}

ACharacter* UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(const UObject* WorldContextObject)
{
	return GetActivePlayerController(WorldContextObject)->GetCharacter();
}

void UMyBlueprintFunctionLibrary::SetupActiveControllerID(const UObject* WorldContextObject, FKey Key, EStatusReturnType& Status)
{
	if (Key.IsGamepadKey())
	{
		for (int32 ControllerIndex = 0; ControllerIndex < UMyGameInstance::MAX_CONTROLLERS; ++ControllerIndex)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, ControllerIndex);
			if (PC->WasInputKeyJustPressed(Key))
			{
				SetActiveControllerID(WorldContextObject, ControllerIndex);
				RemoveAllPlayers(WorldContextObject);
				Status = EStatusReturnType::Success;
				return;
			}
		}
	}

	Status = EStatusReturnType::Fail;
}

