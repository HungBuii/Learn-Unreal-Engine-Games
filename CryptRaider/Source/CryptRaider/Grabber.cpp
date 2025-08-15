// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// if (physicsHandle != nullptr)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Got Physic Handle: %s"), *physicHandle->GetName());
	// }
	// else UE_LOG(LogTemp, Warning, TEXT("No Physic Handle Found"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FRotator myRotator = GetComponentRotation();
	// UE_LOG(LogTemp, Display, TEXT("Grabber Rotation: %s"), *myRotator.ToCompactString());
	//
	// UE_LOG(LogTemp, Display, TEXT("Time: %f"), GetWorld()->TimeSeconds);

	// float damage = 5;
	// if (HasDamage(damage))
	// {
	// 	PrintDamage(damage);
	// }
	// UE_LOG(LogTemp, Display, TEXT("Original Damage: %f"), damage);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) return;

	if (physicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
	
}

// void UGrabber::PrintDamage(const float& damage)
// {
// 	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), damage);
// }
//
// bool UGrabber::HasDamage(float& outDamage)
// {
// 	outDamage = 6;
// 	return true;
// }

void UGrabber::Grab()
{
	UPhysicsHandleComponent* physicHandle = GetPhysicsHandle();
	if (physicHandle == nullptr) return;

	FHitResult hitResult;
	bool hasHit = GetGrabbaleInReach(hitResult);
	
	if (hasHit)
	{
		// DrawDebugSphere(GetWorld(), hitResult.Location, 10, 10, FColor::Green, false, 5);
		// DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		// AActor* hitActor = hitResult.GetActor();
		// UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *hitActor->GetActorNameOrLabel());

		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->WakeAllRigidBodies();
		physicHandle->GrabComponentAtLocationWithRotation(hitComponent,
															NAME_None, hitResult.ImpactPoint,
															GetComponentRotation());
	}
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("No Hit"));
	// }
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr) return;
	if (physicsHandle->GetGrabbedComponent() != nullptr)
	{
		physicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (result == nullptr) UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent"));
	return result;
}

bool UGrabber::GetGrabbaleInReach(FHitResult &outHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;
	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5);
	
	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	return GetWorld()->SweepSingleByChannel(outHitResult, start, end,
												FQuat::Identity, ECC_GameTraceChannel2, sphere);
}

