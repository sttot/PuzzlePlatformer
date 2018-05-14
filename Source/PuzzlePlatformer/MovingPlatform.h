// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:

	AMovingPlatform();
	
	////////////////////////////////////////////////

	// Default platform moving speed - Can edit in editor
	UPROPERTY( EditAnywhere )
	float fSpeed = 20.f;

	////////////////////////////////////////////////////////////////////////
	// Can specify a target location to reach in editor
	// Unassigned means this defaults to ( 0.f, 0.f, 0.f )
	// MakeEditWidget enables in editor moving of a marker 
	// N.B. Any position is relative to centre of cube and not world space
	////////////////////////////////////////////////////////////////////////
	UPROPERTY( EditAnywhere, Meta = ( MakeEditWidget = true ) )
	FVector m_sTargetLocation;

protected:

	virtual void BeginPlay	() override;

	virtual void Tick		( float fDeltaTime ) override;

private:

	// Set desired starting and target positions 
	FVector m_sGlobalTargetLocation;

	FVector m_sGlobalStartLocation;
};
