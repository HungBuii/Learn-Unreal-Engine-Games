// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	/* Move platform forwards
			Get current location
			Add vector to that location
			Set the location
	   Send platform back if gone too far
			Check how far we've moved
			Reverse direction of motion if gone too far
	*/

	FVector currentLocation = GetActorLocation();
	currentLocation += platformVelocity * DeltaTime;
	SetActorLocation(currentLocation);

	float distanceMoved = FVector::Dist(startLocation, currentLocation);

	if (distanceMoved > moveDistance)
	{
		FString name = GetName();
		float overShoot = distanceMoved - moveDistance;
		UE_LOG(LogTemp, Display, TEXT("%s overshoot = %f"), *name, overShoot);
		/*
			https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Logging/ELogVerbosity__Type?application_version=5.6#remarks
			https://cplusplus.com/reference/cstdio/printf/
		 */

		FVector moveDirection = platformVelocity.GetSafeNormal();
		/*
		Gets a normalized copy of the vector, checking it is safe to do so based on the length
		Normalize vector by 1
		*/

		startLocation += moveDirection * moveDistance;
		SetActorLocation(startLocation);
		platformVelocity = -platformVelocity;
	}
	// test = distanceMoved;
}

void AMovingPlatform::RotatePlatform(float DeltaTime) 
{
	UE_LOG(LogTemp, Display, TEXT("Rotating... %s"), *GetName());
}
