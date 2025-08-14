// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


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

	UPhysicsHandleComponent* physicHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicHandle != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Got Physic Handle: %s"), *physicHandle->GetName());
	}
	else UE_LOG(LogTemp, Warning, TEXT("No Physic Handle Found"));
	
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
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;
	DrawDebugLine(GetWorld(), start, end, FColor::Red);

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(hitResult, start, end,
												FQuat::Identity, ECC_GameTraceChannel2, sphere);

	if (hasHit)
	{
		AActor* hitActor = hitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *hitActor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Release grabber!"));
}

