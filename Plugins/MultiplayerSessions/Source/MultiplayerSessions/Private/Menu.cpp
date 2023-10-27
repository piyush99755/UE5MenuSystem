// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

void UMenu::MenuSetup()
{
	//add widget to viewport and set its visibility
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	

	//Set input mode for widget class
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeUIOnly InputDataMode;
		InputDataMode.SetWidgetToFocus(TakeWidget());
		InputDataMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputDataMode);
	}
}
