// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	// Aims toward player
	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptableRadius);

	auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
		
	TankAimingComponent->Fire();
}




