// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Public/UObject/Class.h"
#include "TankPlayerController.generated.h" // Must be the last include


class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
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
