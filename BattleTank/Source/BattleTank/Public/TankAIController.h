// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private: // even though they are private by default (if you don't write anything)
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();

	virtual void SetPawn(APawn* InPawn) override; // called when the pawn is possesed

	UFUNCTION()
	void OnPossessedTankDeath();
protected: 
	// How close can the AI tank get to the player
	UPROPERTY(EditAnywhere, Category = "Setup") // Consider EditDefaultsOnly
	float AcceptanceRadius = 8000; 
};
