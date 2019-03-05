// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void RotateTurret(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 5; // sensible default

	UPROPERTY(EditAnywhere)
		float MinRotationDegress = 0; // sensible default

	UPROPERTY(EditAnywhere)
		float MaxRotationDegrees = 180; // sensible default
};