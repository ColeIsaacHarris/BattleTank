// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

void ATankAIController::AimTowardsPlayer()
{
	if(!GetControlledTank()) { return; }
	FVector PlayerTankPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	GetControlledTank()->AimAt(PlayerTankPosition);
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



