// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystems/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformsGameInstance	( const FObjectInitializer& ObjectInitializer );

	virtual void Init();

	UFUNCTION( BlueprintCallable )
	void LoadMenu();

	UFUNCTION( exec )
	void Host();

	UFUNCTION( exec )
	void Join( const FString& rsAddress );

private:
	TSubclassOf<class UUserWidget> MenuClass;
};
