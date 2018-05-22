// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenuSource.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API UMainMenuSource : public UUserWidget
{
	GENERATED_BODY()

public:

void SetMenuInterface( IMenuInterface* MenuInterface );

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY( meta = ( BindWidget ) )
	class UButton* m_pcHostButton;
	
	UPROPERTY( meta = ( BindWidget ) )
	class UButton* m_pcJoinButton;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	IMenuInterface* m_pcMenuInterface;
};
