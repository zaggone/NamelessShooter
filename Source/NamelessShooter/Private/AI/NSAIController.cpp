// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSAIController.h"
#include "AI/NSAICharacter.h"

void ANSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AIChar = Cast<ANSAICharacter>(InPawn);
	if (AIChar) 
	{
		RunBehaviorTree(AIChar->BehaviorTreeAsset);
	}
}
