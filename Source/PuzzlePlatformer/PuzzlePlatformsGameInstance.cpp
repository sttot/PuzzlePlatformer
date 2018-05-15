// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"

// Will always be called even if the game is not being played
// Output log will generate this every time there is a compile of code
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance( const FObjectInitializer& ObjectInitializer )
{
	UE_LOG( LogTemp, Warning, TEXT( "Game Instance Constructor" ) );
}

// Only occurs when "hitting" play and will occur for each individual player
// Log Output will call this for the same amount of times as the number of players that currently exist
void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG( LogTemp, Warning, TEXT( "Game Instance Init" ) );
}

// exec command that prints debug text to screen in game
void UPuzzlePlatformsGameInstance::Host()
{
	// Pointer to the running engine class 
	UEngine* pcEngine = GetEngine();

	// Ensure there is an Engine running	
	if ( !ensure( pcEngine != nullptr ) ) return;

	pcEngine->AddOnScreenDebugMessage( 0, 2, FColor::Green, TEXT( "Hosting" ) );

	UWorld* pcWorld = GetWorld();

	// Ensure there is a world currently running
	if ( !ensure( pcWorld != nullptr ) ) return;

	// Make the host travel to the map provided as an argument
	// Add ?listen to the end so that this host listen for connections from other clients
	// Ref: https://docs.unrealengine.com/en-us/Programming/Basics/CommandLineArguments under the topic of URL Parameters
	pcWorld->ServerTravel( "/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen" );
}

// exec command that prints debug text to screen in game
void UPuzzlePlatformsGameInstance::Join( const FString& rsAddress )
{
	// Pointer to the running engine class 
	UEngine* pcEngine = GetEngine();

	// Ensure there is an Engine running	
	if ( !ensure( pcEngine != nullptr ) ) return;

	pcEngine->AddOnScreenDebugMessage( 0, 5, FColor::Green, FString::Printf( TEXT( "Hosting %s" ), *rsAddress ) );

	APlayerController* pcPlayerController = GetFirstLocalPlayerController();

	// Ensure there is at least one PlayerController
	if ( !ensure( pcPlayerController != nullptr ) ) return;
	
	// Connect to the server at the address of rsAddress
	pcPlayerController->ClientTravel( rsAddress, ETravelType::TRAVEL_Absolute );
}