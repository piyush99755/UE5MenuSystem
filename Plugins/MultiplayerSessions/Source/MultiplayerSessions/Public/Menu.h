// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		void MenuSetup();

protected:


	virtual bool Initialize() override;

private:

	//specify special type of specifier to bind button to the widget class 
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	//function to bind to the buttons

	UFUNCTION()
		void JoinButtonClicked();

	UFUNCTION()
		void HostButtonClicked();

	//multiplayer sessions subsystem class to handle online sessions functionality
	class UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

};
