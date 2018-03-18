// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else { UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName())); }

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is ticking"))
		AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }
	
	// Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point 

}
