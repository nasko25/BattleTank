// Copyright

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	// Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); a better way to do this:
	Wheel->SetupAttachment(Mass); // <- this works only in the constructor

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	// MassWheelConstraint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MassWheelConstraint->SetupAttachment(Mass);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

