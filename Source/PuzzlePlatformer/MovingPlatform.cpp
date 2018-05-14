// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	// Set actor to be able to tick every frame
	PrimaryActorTick.bCanEverTick = true;

	// Enables Actor to be mobile at runtime
	SetMobility( EComponentMobility::Movable );
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Replicate the behaviour of the platform to all clients connected to the server
	// Only enable this if the code is being executed from the server
	if ( HasAuthority() )
	{
		SetReplicates( true );
		SetReplicateMovement( true ); // Replicate platform movement to clients
	}

	m_sGlobalStartLocation = GetActorLocation();

	m_sGlobalTargetLocation = GetTransform().TransformPosition( m_sTargetLocation );
}

void AMovingPlatform::Tick( float fDeltaTime )
{
	Super::Tick( fDeltaTime );

	// If the code is being run on the server side
	if ( HasAuthority() )
	{
		// First obtain the current location of the platform in world space
		FVector m_sLocation = GetActorLocation();

		float fJourneyLength	= ( m_sGlobalTargetLocation - m_sGlobalStartLocation ).Size();
		float fJourneyTravelled = ( m_sLocation - m_sGlobalStartLocation ).Size();

		// Use .GetSafeNormal as this will safely create a new vector that will not lose accuracy 
		// Use Global Location vectors to ensure that the platform does not glitch out 
		FVector m_sDirection = ( m_sGlobalTargetLocation - m_sGlobalStartLocation ).GetSafeNormal();

		// If direction vector is almost 0, turn the platform direction around
		if (fJourneyTravelled >= fJourneyLength )
		{
			FVector m_sSwap = m_sGlobalStartLocation;
			m_sGlobalStartLocation = m_sGlobalTargetLocation;
			m_sGlobalTargetLocation = m_sSwap;
		}

		// Check direction of platform movement
		// Update position by fSpeed every tick 
		m_sLocation += fSpeed * fDeltaTime * m_sDirection;

		SetActorLocation( m_sLocation );
	}
}
