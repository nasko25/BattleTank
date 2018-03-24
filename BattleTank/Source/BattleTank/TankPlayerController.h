// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Public/UObject/Class.h"
#include "GameFramework/Actor.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	ATank* GetControlledTank() const;
	
private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;
	// start the tank moving the barrow so that a shot would
	// hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;


	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
