// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameModeBase.h"
#include "GameFrameWork/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Orange, FString::Printf(TEXT("Number of Player exists in level: %d"), NumberOfPlayers));
		}

		//to get player name , has to access PlayerState which belongs to controller class
        //get player state and stored in a variable
		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if (PlayerState)
		{
			FString PlayerName = PlayerState->GetPlayerName();

			GEngine->AddOnScreenDebugMessage(1, 50.f, FColor::Cyan, FString::Printf(TEXT("%s has joined the game"), *PlayerName));
		}
		
		
	}
}

void ALobbyGameModeBase::Logout(AController* ExitingPlayer)
{
	    //to get player name , has to access PlayerState which belongs to controller class
		//get player state and stored in a variable
        APlayerState* PlayerState = ExitingPlayer->GetPlayerState<APlayerState>();
		if (PlayerState)
        {
			int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(1, 50.f, FColor::Orange, FString::Printf(TEXT("Number of Player exists in level: %d"), NumberOfPlayers));
			}
			FString PlayerName = PlayerState->GetPlayerName();

			GEngine->AddOnScreenDebugMessage(1, 50.f, FColor::Cyan, FString::Printf(TEXT("%s has left the game"), *PlayerName));
		}


	
}
