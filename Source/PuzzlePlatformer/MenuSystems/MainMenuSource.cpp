// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuSource.h"

#include "Components/Button.h"

bool UMainMenuSource::Initialize()
{
	bool bSuccess = UUserWidget::Initialize();
	if ( !bSuccess )
	{
		return false;
	}

	if ( !ensure( m_pcHostButton != nullptr ) ) return false;

	m_pcHostButton->OnClicked.AddDynamic( this, &UMainMenuSource::HostServer );

	m_pcJoinButton->OnClicked.AddDynamic( this, &UMainMenuSource::JoinServer );

	return true;
}

void UMainMenuSource::SetMenuInterface( IMenuInterface* MenuInterface )
{
	this->m_pcMenuInterface = MenuInterface;
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

}

