// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {Reloading, Aiming, Locked};

// Forward declarations
class UTankBarrel; 
class UTankTurret;
class AShellProjectile;

// Hold Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	// Calculates a HitLocation based on the LaunchSpeed and moves the barrel and turret to aim at that HitLocation
	void AimAt(FVector HitLocation);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AShellProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000; // TODO Find sensible default value
	
	float ReloadTimeInSeconds = 3.0;
	FVector AimDirection;
	double LastFireTime = 0;

	// Takes in AimDirection from AimAt and calls move/rotate functions on both Barrel and Turret respectively with appropriate rotation values
	void MoveBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving();
};
