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

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Display, TEXT("Trigger Component is Ticking!"));

	AActor* actor = GetAcceptableActor();
	if (actor != nullptr)
	{
		// UE_LOG(LogTemp, Display, TEXT("Unlocking...!"));
		
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != nullptr)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		mover->SetShouldMove(true);
	}
	else
	{
		// UE_LOG(LogTemp, Display, TEXT("Relocking...!"));
		mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* newMover)
{
	mover = newMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	/* Method 1 (while) */
	// int index = 0;
	// while (index < actors.Num())
	// {
	// 	FString actorName = actors[index]->GetActorNameOrLabel();
	// 	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *actorName);
	// 	++index;
	// }

	/* Method 2 (for) */
	// for (int i = 0; i < actors.Num(); i++)
	// {
	// 	FString actorName = actors[i]->GetActorNameOrLabel();
	// 	UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *actorName);
	// }

	/* Method 3 (foreach) */
	for (AActor* actor : actors)
	{
		// FString actorName = actor->GetActorNameOrLabel();
		// UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *actorName);
		if (actor->ActorHasTag(acceptableActorTag))
		{
			// UE_LOG(LogTemp, Display, TEXT("Unlocking...!"));
			return actor;
		}
	}
	return nullptr;
}
