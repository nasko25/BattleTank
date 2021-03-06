// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "CoreMinimal.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay(); // Needed for BP Begin Play to run!!!
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); // ? is it needed
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage Amount = %f, Damage To Apply = %i"), DamageAmount, DamageToApply)

	return DamageToApply;
}

float ATank::GetHealthPercent() const{
	return (float)CurrentHealth / (float)StartingHealth;
}


/* Actors do not have child actors, this is a misconsception. What happens is the COMPONENTS of the actors have child components, and the 
effect of this is that it seems as if the actors have child actors, when in fact only scene components in these actors have child components. 
See heirarchy in Attachment, Actors and Components lecture */