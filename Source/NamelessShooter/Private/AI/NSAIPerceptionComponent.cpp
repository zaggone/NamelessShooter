// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/NSAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/NSHealthComponent.h"
#include "Perception/AISense_Sight.h"

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

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = PercieveActor->FindComponentByClass<UNSHealthComponent>();

		const auto PercievePawn = Cast<APawn>(PercieveActor);

		//const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->GetController());

		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}
	return BestPawn;
}