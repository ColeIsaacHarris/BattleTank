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

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}