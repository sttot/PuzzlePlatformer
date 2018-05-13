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

	////////////////////////////////////////////////
	// Editable variable float of platform speeds
	////////////////////////////////////////////////
	UPROPERTY( EditAnywhere )
	float fPlatformSpeedX = 10.f;

	UPROPERTY( EditAnywhere )
	float fPlatformSpeedY = 0.f;

	UPROPERTY( EditAnywhere )
	float fPlatformSpeedZ = 0.f;

protected:

	virtual void Tick ( float fDeltaTime ) override;
};
