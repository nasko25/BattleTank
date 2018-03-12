// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank.h"
#include "Public/UObject/Class.h"
#include "GameFramework/Actor.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h" 


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else { UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *(ControlledTank->GetName())); }

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
