// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // must be at bottom

// Forward Declarations
class UTankAimingComponent;
class UTankBarrel;
class AShellProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void Initialize(UTankBarrel* BarrelToSet, UTankAimingComponent* TankAimingComponentToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr; // Local TankAimingComponent reference	

private:	
	// Sets default values for this pawn's properties
	ATank();

	//called on begin play
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000; // TODO Find sensible default value

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AShellProjectile> ProjectileBlueprint; 

	float ReloadTimeInSeconds = 3.0;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; // Local Barrel reference for spawning projectile
};
