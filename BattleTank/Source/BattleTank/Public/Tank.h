// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	

private:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; // alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf 

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
public: 
	UFUNCTION(BlueprintCallable, Category = Setup) // makes it a method that you can call from blueprint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup) // makes it a method that you can call from blueprint
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
};
