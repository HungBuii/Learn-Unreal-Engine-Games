// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (OwnerController)	
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
		
		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;
		
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		if (bool IsHit = GetWorld()->LineTraceSingleByChannel
			(HitResult, ViewPointLocation, EndLocation, ECC_GameTraceChannel2, Params))
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.f, 16, FColor::Red, true);
		}
		// DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f, 2.f, FColor::Red, true);
	}
}

