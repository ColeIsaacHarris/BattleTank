// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 10; // sensible default

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegress = 0; // sensible default

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 15; // sensible default
};
