// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Foward declarations

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

protected:

	// How close the AI tank will get to player before stopping
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // Consider EditDefaultsOnly
	float AcceptableRadius = 1000.0f;
	
private:

	// called every frame
	virtual void Tick(float DeltaTime) override;

	// called at begin play
	virtual void BeginPlay() override;

};

