// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"




void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("TANK DIED"))
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is ticking"))
		AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; } // e.g. if not posessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}
	
	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString()); // basically you 
		//always want something in "", when logging a TEXT.

		AimingComponent->AimAt(HitLocation);
	}
}
// Get world location of linetrace through crosshair, true hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const{

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	// UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())
		// "De-project" the screen position of the crosshair to a wprld direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString())
			// Line trace along that LookDirection, and see what we hit (up to max range)

		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	

	return false;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility // hit what is visible
		)) {
		// set hitlocation from HitResult out parameter
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // LineTrace did not succeed
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation[0], 
		ScreenLocation.Y /*same as the previous one; different syntax*/, 
		CameraWorldLocation, 
		LookDirection);
}

