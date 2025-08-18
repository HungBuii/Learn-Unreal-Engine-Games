// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// UE_LOG(LogTemp, Display, TEXT("Constructing!"));
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive!"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Display, TEXT("Trigger Component is Ticking!"));

	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	if (actors.Num() > 0)
	{
		FString actorName = actors[0]->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *actorName);
	}
}