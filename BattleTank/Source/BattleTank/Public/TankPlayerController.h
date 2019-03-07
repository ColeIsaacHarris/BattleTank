// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // always last include

// Forward declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// gets controlled tank
	ATank * GetControlledTank() const;

private:

	// called every frame
	virtual void Tick(float DeltaTime) override;

	//called on begin play
	virtual void BeginPlay() override;

	// Calls GetSightRayHitLocation returning Line Trace OutHitLocation, then calls Tank AimAt feeding in OutHitLocation
	void AimTowardsCrosshair();

	// Get and return the location of linetrace intersection through crosshair to landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const;
};
