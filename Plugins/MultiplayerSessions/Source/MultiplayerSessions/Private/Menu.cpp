// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup()
{
	//add widget to viewport and set its visibility
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	
	UWorld* World = GetWorld();
	if (World)
	{
		//Set input mode for widget class
		APlayerController* PlayerController = World->GetFirstPlayerController();

		if (PlayerController)
		{
			FInputModeUIOnly InputDataMode;
			InputDataMode.SetWidgetToFocus(TakeWidget());
			InputDataMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputDataMode);
		}
	}

	//get hold of reference of game instance, which will be using to get multiplayer sessions subsystem class 
	UGameInstance* GameInstance = GetGameInstance();

	if (GameInstance)
	{
		//getting sub system setting value of pointer MultiplayerSessionsSubsystem
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	//bind function to buttons
	HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);

	return true;
	
}

void UMenu::HostButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Host button clicked")));
	}

	//on host button clicked, create session and travel to lobby level
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll"));

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(FString("/Game/ThirdPerson/Maps/Lobby?listen"));
		}
	}
	
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Join button clicked")));
	}
}


