// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuSource.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/WidgetSwitcher.h"

bool UMainMenuSource::Initialize()
{
	bool bSuccess = UUserWidget::Initialize();
	if ( !bSuccess )
	{
		return false;
	}

	if ( !ensure( m_pcHostButton != nullptr ) )				return false;
	m_pcHostButton->OnClicked.AddDynamic( this, &UMainMenuSource::HostServer );

	if ( !ensure( m_pcConfirmJoinMenuButton != nullptr ) )	return false;
	m_pcConfirmJoinMenuButton->OnClicked.AddDynamic( this, &UMainMenuSource::JoinServer );

	if ( !ensure( m_pcJoinButton != nullptr ) )				return false;
	m_pcJoinButton->OnClicked.AddDynamic( this, &UMainMenuSource::OpenJoinMenu );

	if ( !ensure( m_pcCancelJoinMenuButton != nullptr ) )	return false;
	m_pcCancelJoinMenuButton->OnClicked.AddDynamic( this, &UMainMenuSource::OpenMainMenu );


	return true;
}	

void UMainMenuSource::SetMenuInterface( IMenuInterface* MenuInterface )
{
	this->m_pcMenuInterface = MenuInterface;
}

void UMainMenuSource::Setup()
{
	// Add userwidget to viewport
	this->AddToViewport();

	UWorld* m_pcWorld = GetWorld();

	// Ensure there is a valid world
	if ( !ensure( m_pcWorld != nullptr ))			return;

	APlayerController* pcPlayerController = m_pcWorld->GetFirstPlayerController();

	// Ensure there is at least one PlayerController
	if ( !ensure( pcPlayerController != nullptr ) ) return;

	// Set input to take in only UI functionality
	// Ref: http://api.unrealengine.com/INT/API/Runtime/Engine/GameFramework/FInputModeUIOnly/index.html
	// TakeWidget Ref: http://api.unrealengine.com/INT/API/Runtime/UMG/Components/UWidget/TakeWidget/index.html
	// MouseLockMode Ref: http://api.unrealengine.com/INT/API/Runtime/Engine/Engine/EMouseLockMode/index.html
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus( this->TakeWidget() );
	InputModeData.SetLockMouseToViewportBehavior( EMouseLockMode::DoNotLock );

	// Once set, initialise input mode to player
	pcPlayerController->SetInputMode( InputModeData );

	// Enable mouse cursor to be shown
	pcPlayerController->bShowMouseCursor = true;
}

void UMainMenuSource::Teardown()
{
	this->RemoveFromViewport();

	UWorld* m_pcWorld = GetWorld();

	// Ensure there is a valid world
	if ( !ensure( m_pcWorld != nullptr ) )			return;

	APlayerController* pcPlayerController = m_pcWorld->GetFirstPlayerController();

	// Ensure there is at least one PlayerController
	if ( !ensure( pcPlayerController != nullptr ) ) return;

	// Set input to take in only game world functionality
	FInputModeGameOnly InputModeData;

	pcPlayerController->SetInputMode( InputModeData );

	// Disable mouse cursor
	pcPlayerController->bShowMouseCursor = false;

}

void UMainMenuSource::HostServer()
{
	if ( m_pcMenuInterface != nullptr )
	{
		m_pcMenuInterface->Host();
	}

	UE_LOG( LogTemp, Warning, TEXT( "I'm gonna host a server!" ) );
}

void UMainMenuSource::JoinServer()
{
	if ( m_pcMenuInterface != nullptr )
	{
		if ( !ensure ( m_pcIPAddressField != nullptr ) ) return;
		const FString& cAddress = m_pcIPAddressField->GetText().ToString();
		m_pcMenuInterface->Join( cAddress );
	}
}

void UMainMenuSource::OpenJoinMenu()
{
	if ( !ensure ( m_pcMenuSwitcher != nullptr ) )	return;
	if ( !ensure ( JoinMenu != nullptr ) )			return;

	m_pcMenuSwitcher->SetActiveWidget( JoinMenu );
}

void UMainMenuSource::OpenMainMenu()
{
	if ( !ensure ( m_pcMenuSwitcher != nullptr ) )	return;
	if ( !ensure ( MainMenu != nullptr ) )			return;

	m_pcMenuSwitcher->SetActiveWidget( MainMenu );
}

