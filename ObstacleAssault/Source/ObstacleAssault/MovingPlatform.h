// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Moving")
	FVector platformVelocity = FVector(100, 0, 0);
	UPROPERTY(EditAnywhere, Category="Moving")
	float moveDistance = 100;
	UPROPERTY(EditAnywhere, Category="Rotating")
	FRotator rotationVelocity = FRotator(0, 0, 0);
	UPROPERTY(VisibleAnywhere, Category="Rotating")
	float test = 0;
	
	FVector startLocation = FVector(0, 0, 0);

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformReturn() const;
	float GetDistanceMoved() const;
};
