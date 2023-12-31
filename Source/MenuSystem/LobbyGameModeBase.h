// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MENUSYSTEM_API ALobbyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer);

	virtual void Logout(AController* ExitingPlayer);
	
};
