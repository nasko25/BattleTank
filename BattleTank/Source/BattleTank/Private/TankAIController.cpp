// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
//#include "Public/UObject/Class.h"
#include "GameFramework/Actor.h"


#pragma once
// Depends on movement component via pathfinding system.

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
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO fix firing
	// ControlledTank->Fire(); // TODO limit fire rate

}