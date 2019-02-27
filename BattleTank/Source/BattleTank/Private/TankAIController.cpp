// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Tank found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Current Player Tank is: %s"), *(PlayerTank->GetName()));
	}
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


