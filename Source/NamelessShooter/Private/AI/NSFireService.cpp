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

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto Character = Cast<ANSBaseCharacter>(Controller->GetPawn());
		if (Character)
		{
			Character->Shot();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}
