// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ControllerDisconnectedWidget.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GROUP6IX_MONDAY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	FTSTicker::FDelegateHandle TickDelegateHandle;
	int32 ActiveControllerId = -1;

	void HandleControllerConnectionChange(bool bConnected, FPlatformUserId UserId, int32 ControllerId);

	bool bDidContronllerDisconnectPauseGame = false;

public:
	static const int32 MAX_CONTROLLERS = 4;

	virtual void Init() override;
	virtual void Shutdown() override;

	bool Tick(float DeltaSeconds);

	void SetActiveControllerID(int32 ControllerID);
	int32 GetActiveControllerID();

	UPROPERTY()
		UControllerDisconnectedWidget* ControllerDisconnectedWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UControllerDisconnectedWidget> ControllerDisconnectedWidgetClass;
};
