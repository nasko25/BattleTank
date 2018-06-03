// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;

}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	// reset the throttle
	CurrentThrottle = 0;
}
void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slipage speed 	// Work-out the required acceleration this frame to correct 
	auto SlipageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlipageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways force ( F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2, 2);
}

void UTankTrack::DriveTrack() {
	//	auto Time = GetWorld()->GetTimeSeconds();
	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle)*/

	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		//UE_LOG(LogTemp, Warning, TEXT("MOVING!"))
	}
}


