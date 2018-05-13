// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	// Set actor to be able to tick every frame
	PrimaryActorTick.bCanEverTick = true;

	// Enables Actor to be mobile at runtime
	SetMobility( EComponentMobility::Movable );
}

void AMovingPlatform::Tick( float fDeltaTime )
{
	Super::Tick( fDeltaTime );

	// If the code is being run on the server side
	if ( HasAuthority() )
	{
		FVector m_sLocation = GetActorLocation();

		// Update position by 5 cm/s 
		m_sLocation += FVector( fPlatformSpeedX * fDeltaTime, fPlatformSpeedY, fPlatformSpeedZ );

		SetActorLocation( m_sLocation );
	}
}
