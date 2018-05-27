// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

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

	virtual void BeginPlay() override;

	// TODO remove once firing is moved to aiming component
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; // alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf 

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO Remove


	UPROPERTY(EditDefaultsOnly, Category = "Firing") // May cause error
	float ReloadTimeInSeconds = 3;
	
	double LastFireTime = 0;
public: 
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
};
