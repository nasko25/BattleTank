// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
//#include "Public/UObject/Class.h"
#include "GameFramework/Actor.h"


#pragma once


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	/* auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else { UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *(ControlledTank->GetName())); }
	if (!PlayerTank) {
	UE_LOG(LogTemp, Warning, TEXT("AI Controller cannot find player tank."))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *(PlayerTank->GetName()))
	}
	*/
	}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankAIController::AimTowardsCrosshair() {
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank) {
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire(); // TODO limit fire rate
	}


}