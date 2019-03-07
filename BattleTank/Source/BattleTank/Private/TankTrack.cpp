// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto TrackName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *TrackName, Throttle);

	// TODO clamp actual throttle value to -1 to +1 so player can't over-drive 
	auto ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


