// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	ATank * GetControlledTank() const;
	
private:
	
	// Aims toward current player
	void AimTowardsPlayer();

	// called every frame
	virtual void Tick(float DeltaTime) override;

	// called at begin play
	virtual void BeginPlay() override;

};

