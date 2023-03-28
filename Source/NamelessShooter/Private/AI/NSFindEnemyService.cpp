// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSFindEnemyService.h"
#include "AI/NSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UNSFindEnemyService::UNSFindEnemyService()
{

}

void UNSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<UNSAIPerceptionComponent>();
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
