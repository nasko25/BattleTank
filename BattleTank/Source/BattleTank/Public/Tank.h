// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

	// virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
	
public: 
	// Called by the engine, when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Returns current health as a percentage of stating health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")    // https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Reference/Functions/Specifiers/BlueprintPure
	float GetHealthPercent() const;
};
