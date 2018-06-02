// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;

}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("Track hit"))
}
void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate the slipage speed
	auto SlipageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out the required acceleration this frame to correct 
	auto CorrectionAcceleration = -SlipageSpeed / DeltaTime * GetRightVector(); 
	// Calculate and apply sideways force ( F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); 
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
//	auto Time = GetWorld()->GetTimeSeconds();
	/*auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle)*/

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); 
	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		//UE_LOG(LogTemp, Warning, TEXT("MOVING!"))
	}
}


