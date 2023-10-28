// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "OnlineSubsystem.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;

	//add widget to viewport and set its visibility
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;
	
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
			PlayerController->SetShowMouseCursor(true);
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

void UMenu::MenuTearDown()
{
	//removing widget from parent widget
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		//set input mode to game only after tear down menu widget
		APlayerController* PlayerController = World->GetFirstPlayerController();
		FInputModeGameOnly InputModeData;
		
		PlayerController->SetInputMode(InputModeData);
		PlayerController->SetShowMouseCursor(false);
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

void UMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	//this is inherit function from UUserWidget class 
	//as host button is clicked along with travelling to lobby level , it removes menu widget too

	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
	MenuTearDown();
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
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);

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


