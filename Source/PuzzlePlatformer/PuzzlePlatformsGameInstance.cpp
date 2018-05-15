// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

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

