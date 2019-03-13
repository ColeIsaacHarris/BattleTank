// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
	else { UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find AimingComponent on BeginPlay")); }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!ensure(GetControlledTank())) { return; }

	FVector OutHitLocation(0); // Out parameter
	if (ensure(GetSightRayHitLocation(OutHitLocation)))
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

// Get world location of linetrace intersection with landscape, returns true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in screen space
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ReticleScreenLocation(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	// "De-Project the screen position of the reticle to world space
	FVector LookDirection;
	if (ensure(GetLookDirection(ReticleScreenLocation, LookDirection))) 
	{
		// line trace along  and see what we hit
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false; // line trace did not succeed
}

// Gets a vector from the screen position of the Reticle (ReticleScreenLocation)
bool ATankPlayerController::GetLookDirection(FVector2D ReticleScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ReticleScreenLocation.X, ReticleScreenLocation.Y, CameraWorldLocation, LookDirection);
}
