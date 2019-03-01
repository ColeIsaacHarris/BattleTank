// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank){
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing a Tank"), ControlledTank);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing: %s"), *(ControlledTank->GetName()));
	}
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
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) 
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		// If it hits the landscape
			// Tell the controlled tank to aim at this point
	};
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
	FVector HitLocation;
	if (GetLookDirection(ReticleScreenLocation, LookDirection)) 
	{
		// line trace along  and see what we hit
		GetLookVectorHitLocation(HitLocation, LookDirection);
		UE_LOG(LogTemp, Warning, TEXT("Hit Location is: %s"), *(HitLocation.ToString()));
	};	

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.ImpactPoint;
		return true;
	}
	else
	{
		return false;
	};
}

// Gets a vector from the screen position of the Reticle (ReticleScreenLocation)
bool ATankPlayerController::GetLookDirection(FVector2D ReticleScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ReticleScreenLocation.X, ReticleScreenLocation.Y, CameraWorldLocation, LookDirection);
}
