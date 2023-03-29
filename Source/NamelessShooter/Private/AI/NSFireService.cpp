// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/NSWeaponComponent.h"
#include "Player/NSBaseCharacter.h"

UNSFireService::UNSFireService()
{

}

void UNSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));

	if (Controller && EnemyActor)
	{
		const auto Character = Cast<ANSBaseCharacter>(Controller->GetPawn());
		if (Character)
		{
			Character->Shot();
			Blackboard->SetValueAsVector(EnemyLocationCacheKey.SelectedKeyName, EnemyActor->GetActorLocation());
			Blackboard->SetValueAsBool(HasEnemyLocationCacheKey.SelectedKeyName, true);
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
