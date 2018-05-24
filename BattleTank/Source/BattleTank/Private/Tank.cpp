// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "CoreMinimal.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s SOMETHING_FUNNY: Tank C++ Construct"), *TankName)
}

void ATank::BeginPlay() {
	Super::BeginPlay(); // Needed for BP Begin Play to run!!!
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s SOMETHING_FUNNY: Tank C++ Begin Play"), *TankName)
}

void ATank::AimAt(FVector HitLocation) {
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
	if (!ensure(Barrel)) { return; }
	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:Tank fires"), Time)*/
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds; // more precise time than GetWorld()->GetTimeSeconds();
	if (isReloaded) {
		// Spawn a projectile in the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}