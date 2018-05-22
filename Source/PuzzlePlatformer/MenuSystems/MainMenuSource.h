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

	void Setup();

	void Teardown();

protected:

	virtual bool Initialize() override;

private:

	UPROPERTY( meta = ( BindWidget ) )
	class UButton*			m_pcHostButton;
	
	UPROPERTY( meta = ( BindWidget ) )
	class UButton*			m_pcJoinButton;

	UPROPERTY( meta = ( BindWidget ) )
	class UButton*			m_pcCancelJoinMenuButton;

	UPROPERTY( meta = ( BindWidget ) )
	class UButton*			m_pcConfirmJoinMenuButton;

	UPROPERTY( meta = ( BindWidget ) )
	class UWidgetSwitcher*	m_pcMenuSwitcher;

	UPROPERTY( meta = ( BindWidget ) )
	class UWidget*			MainMenu;

	UPROPERTY( meta = ( BindWidget ) )
	class UWidget*			JoinMenu;

	UPROPERTY( meta = ( BindWidget ) )
	class UEditableTextBox*	m_pcIPAddressField;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenMainMenu();

	IMenuInterface* m_pcMenuInterface;
};
