// Copyright Epic Games, Inc. All Rights Reserved.

#include "RobotShooterGameMode.h"

#include "RobotShooterCharacter.h"
#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"

ARobotShooterGameMode::ARobotShooterGameMode()
{
	// stub
}

void ARobotShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	ARobotShooterCharacter* Player = Cast<ARobotShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);
	
	/*
	int32 LoopIndex = 0;
	while (LoopIndex < ShooterAIActors.Num())
	{
		AActor* ShooterAIActor = ShooterAIActors[LoopIndex];

		LoopIndex++;
	}
	*/
	
	for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++)
	{
		AActor* ShooterAIActor = ShooterAIActors[LoopIndex];
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);
		
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
			UE_LOG(LogTemp, Display, TEXT("%s starting behavior tree"), *ShooterAI->GetActorNameOrLabel());
		}
	}
}
