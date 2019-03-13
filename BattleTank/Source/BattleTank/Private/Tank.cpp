// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "ShellProjectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

/*void ATank::Initialize(UTankBarrel* BarrelToSet, UTankAimingComponent* TankAimingComponentToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent = TankAimingComponentToSet;
}*/

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded) 
	{
		// Spawn projectile at socket location on barrel
		auto Projectile = GetWorld()->SpawnActor<AShellProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("ProjectileFiringLocation")), Barrel->GetSocketRotation(FName("ProjectileFiringLocation")));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

