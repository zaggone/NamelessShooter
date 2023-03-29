// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NSAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/NSHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/NSBaseCharacter.h"

UNSAIPerceptionComponent::UNSAIPerceptionComponent()
{

}

AActor* UNSAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Character = Cast<ANSBaseCharacter>(Controller->GetPawn());
	if (!Character || !Character->IsArmed()) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = PercieveActor->FindComponentByClass<UNSHealthComponent>();

		const auto PercieveCharacter = Cast<ANSBaseCharacter>(PercieveActor);

		const auto AreEnemies = PercieveCharacter && PercieveCharacter->GetTeamID() == Character->GetTeamID();

		if (HealthComponent && !HealthComponent->IsDead() && !AreEnemies)
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Character->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}
	return BestPawn;
}