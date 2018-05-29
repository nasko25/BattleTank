// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading, 
	Aiming,
	Locked
};

// Forward Declaration (so that we can reference the UTankBarrel type in the declaration of Barrel)
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initilise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


public:	

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UTankBarrel* Barrel = nullptr; 
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000;

	void MoveBarrelTowards(FVector AimDirection);


	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; // alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf 



	UPROPERTY(EditDefaultsOnly, Category = "Firing") // May cause error
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
