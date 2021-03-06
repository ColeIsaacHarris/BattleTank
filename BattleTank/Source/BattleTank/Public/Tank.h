// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Delegates/Delegate.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be at bottom

// Forward Declarations

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

public:
	// Called by the engine when actor takes damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	FTankDelegate OnDeath;

	// Returns current health as a precentage of starting health between 0 - 1 
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

private:
	// Sets default values for this pawn's properties
	ATank();

	//called on begin play
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized in BeginPlay

};