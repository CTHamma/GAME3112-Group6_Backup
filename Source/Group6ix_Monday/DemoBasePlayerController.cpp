// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoBasePlayerController.h"

void ADemoBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		FInputActionBinding& ToggleSafeZoneMode = InputComponent->BindAction("ToggleSafeZoneMode",
			IE_Pressed, this, &ADemoBasePlayerController::ToggleSafeZoneMode);
		ToggleSafeZoneMode.bExecuteWhenPaused = true;
		FInputActionBinding& ToggleSafeZoneRatio = InputComponent->BindAction("ToggleSafeZoneRatio",
			IE_Pressed, this, &ADemoBasePlayerController::ToggleSafeZoneRatio);
		ToggleSafeZoneRatio.bExecuteWhenPaused = true;
	}
};

void ADemoBasePlayerController::ToggleSafeZoneMode()
{
	static bool TitleMode = true;
	FString command = FString::Printf(TEXT("r.DebugSafeZone.Mode %s"), TitleMode ? "1" : "0");
	this->ConsoleCommand(*command);
	TitleMode = !TitleMode;
}

void ADemoBasePlayerController::ToggleSafeZoneRatio()
{
	static bool TitleRatios = true;
	FString command = FString::Printf(TEXT("r.DebugSafeZone.TitleRatio %f"), TitleRatios ? 0.8 : 0.9);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, command);
	this->ConsoleCommand(*command);
	TitleRatios = !TitleRatios;
}
