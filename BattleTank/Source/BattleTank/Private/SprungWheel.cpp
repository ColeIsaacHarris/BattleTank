// Copyright Cole Harris

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SuspensionConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Suspension Constraint"));
	SetRootComponent(SuspensionConstraint);

	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetupAttachment(SuspensionConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Wheel Constraint"));
	WheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{	
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupWheelConstraints();
}

void ASprungWheel::SetupWheelConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	SuspensionConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	WheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		ForceToApplyThisFrame = 0.0f;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	ForceToApplyThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalInpulse, const FHitResult& Hit)
{
	ApplyDrivingForce();
	// UE_LOG(LogTemp, Warning, TEXT("OnHit %f"), GetWorld()->GetTimeSeconds());
}

void ASprungWheel::ApplyDrivingForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * ForceToApplyThisFrame);
}
