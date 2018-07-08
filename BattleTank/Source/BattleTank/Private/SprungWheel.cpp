// Copyright

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(MassWheelConstraint);

	
	/* Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	// Mass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Mass->SetupAttachment(MassWheelConstraint); */


	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle")); // it is USphereComponent and not UStaticMeshComponent, because we want it
	// to be able to simulate physics
	Axle->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	// Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); a better way to do this:
	Wheel->SetupAttachment(Axle); // <- this works only in the constructor


	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle); 
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();

	
}

void ASprungWheel::SetupConstraint() {
	if (!GetAttachParentActor()) return; // gets the tank 
	UE_LOG(LogTemp, Warning, TEXT("Not Null: %s"), *GetAttachParentActor()->GetName())
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

