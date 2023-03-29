// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSAICharacter.h"
#include "AI/NSAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

ANSAICharacter::ANSAICharacter()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ANSAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator{ 0.0f, 200.0f, 0.0f };
	}
	//ToMovePoints.Add(GetActorLocation());
}

void ANSAICharacter::OnDeath()
{
	Super::OnDeath();
	const auto AIController = Cast<AAIController>(Controller);

	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}

}


