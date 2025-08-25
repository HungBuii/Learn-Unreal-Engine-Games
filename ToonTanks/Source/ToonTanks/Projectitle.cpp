// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectitle.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectitle::AProjectitle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectitleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectitleMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f; 
}

// Called when the game starts or when spawned
void AProjectitle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectitle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

