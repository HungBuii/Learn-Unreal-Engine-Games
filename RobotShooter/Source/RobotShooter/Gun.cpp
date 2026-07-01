// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

/* Demo Macros */
#define PI 3.14159f
#define LOG(x) UE_LOG(LogTemp, Display, TEXT(x))
#define LOG_WARNING(x) UE_LOG(LogTemp, Warning, TEXT(x))

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneRoot);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(SceneRoot);
	
	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>("MuzzleFlash");
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);
	
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	MuzzleFlashParticleSystem->Deactivate();
	
	/* Test Macros Demo */
	// UE_LOG(LogTemp, Display, TEXT("The number pi is %f"), PI);
	// LOG("Hello"); // UE_LOG(LogTemp, Display, TEXT("Hello"))
	// LOG_WARNING("This is a warning!"); // UE_LOG(LogTemp, Warning, TEXT("This is a warning!"))
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	MuzzleFlashParticleSystem->Activate(true);
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation());
	
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
			// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.f, 16, FColor::Red, true);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactParticleSystem, 
				HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
			
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);
			
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UGameplayStatics::ApplyDamage(HitActor, BulletDamage, 
					OwnerController, this, UDamageType::StaticClass());
			}
		}
		// DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 90.f, 2.f, FColor::Red, true);
	}
}

