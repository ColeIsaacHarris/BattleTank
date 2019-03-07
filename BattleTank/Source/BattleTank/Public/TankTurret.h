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
	// Rotates the turret Yaw to point toward AimDirection fed in by AimingComponent
	void RotateTurret(float RelativeSpeed); 
	
private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 24; // sensible default
};