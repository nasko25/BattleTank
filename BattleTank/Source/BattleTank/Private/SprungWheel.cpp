// Copyright

#include "SprungWheel.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"


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

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	// Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); a better way to do this:
	Wheel->SetupAttachment(MassWheelConstraint); // <- this works only in the constructor


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();

	
}

void ASprungWheel::SetupConstraints() {
	if (!GetAttachParentActor()) return; // gets the tank 
	UE_LOG(LogTemp, Warning, TEXT("Not Null: %s"), *GetAttachParentActor()->GetName())
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

