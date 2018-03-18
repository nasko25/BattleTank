// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Public/UObject/Class.h"
#include "GameFramework/Actor.h"
#include "Public/Tank.h"
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
	// start the tank moving the barrow so that a shot would
	// hit where the crosshair intersects the world
	void AimTowardsCrosshair();
};
