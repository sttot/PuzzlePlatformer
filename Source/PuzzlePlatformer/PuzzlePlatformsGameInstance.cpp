// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystems/MainMenuSource.h"

////////////////////////////////////////////////////////////////////////////////////////////////
// Will always be called even if the game is not being played
// Output log will generate this every time there is a compile of code
////////////////////////////////////////////////////////////////////////////////////////////////
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance( const FObjectInitializer& ObjectInitializer )
{
	UE_LOG( LogTemp, Warning, TEXT( "Game Instance Constructor" ) );

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass( TEXT( "/Game/MenuSystems/WBP_MainMenu" ) );

	if ( !ensure( MenuBPClass.Class != nullptr ) ) return;

	MenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<APlatformTrigger> PlatformTriggerBPClass( TEXT( "/Game/PuzzlePlatormer/BP_MyPlatformTrigger" ) );
	
	if ( !ensure( PlatformTriggerBPClass.Class != nullptr ) ) return;
	
	UE_LOG( LogTemp, Warning, TEXT( "Found class %s"), *PlatformTriggerBPClass.Class->GetName() );
}

////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// Only occurs when "hitting" play and will occur for each individual player
// Log Output will call this for the same amount of times as the number of players that currently exist
////////////////////////////////////////////////////////////////////////////////////////////////
void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG( LogTemp, Warning, TEXT( "Game Instance Init" ) );

	UE_LOG( LogTemp, Warning, TEXT( "Found class %s" ), *MenuClass->GetName() );
}

////////////////////////////////////////////////

// Initialise the menu widget from BP Class
void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if ( !ensure( MenuClass != nullptr ) ) return;

	m_pcMenu = CreateWidget<UMainMenuSource>( this, MenuClass );

	m_pcMenu->Setup();
	m_pcMenu->SetMenuInterface( this );
}

////////////////////////////////////////////////

// exec command that prints debug text to screen in game
void UPuzzlePlatformsGameInstance::Host()
{
	if ( m_pcMenu != nullptr )
	{
		m_pcMenu->Teardown();
	}

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

////////////////////////////////////////////////

// exec command that prints debug text to screen in game
void UPuzzlePlatformsGameInstance::Join( const FString& rsAddress )
{
	if ( m_pcMenu != nullptr )
	{
		m_pcMenu->Teardown();
	}

	// Pointer to the running engine class 
	UEngine* pcEngine = GetEngine();

	// Ensure there is an Engine running	
	if ( !ensure( pcEngine != nullptr ) ) return;

	pcEngine->AddOnScreenDebugMessage( 0, 5, FColor::Green, FString::Printf( TEXT( "Joining %s" ), *rsAddress ) );

	APlayerController* pcPlayerController = GetFirstLocalPlayerController();

	// Ensure there is at least one PlayerController
	if ( !ensure( pcPlayerController != nullptr ) ) return;
	
	// Connect to the server at the address of rsAddress
	pcPlayerController->ClientTravel( rsAddress, ETravelType::TRAVEL_Absolute );
}