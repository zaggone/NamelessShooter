// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSChangeMoveToTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/NSAICharacter.h"

int32 PointsIter = 0;

UNSChangeMoveToTask::UNSChangeMoveToTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UNSChangeMoveToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto AICharacter = Cast<ANSAICharacter>(Controller->GetPawn());
	if (!AICharacter) return EBTNodeResult::Failed;

	const auto MoveToPoints = AICharacter->GetToMovePoints();
	if (MoveToPoints.Num() == 0) 
	{
		const auto SelfActor = Cast<AActor>(Blackboard->GetValueAsObject(SelfActorKey.SelectedKeyName));
		if(!SelfActor) return EBTNodeResult::Failed;

		Blackboard->SetValueAsVector(MoveToLocationKey.SelectedKeyName, SelfActor->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}

	if (MoveToPoints.Num() == 1)
	{
		Blackboard->SetValueAsVector(MoveToLocationKey.SelectedKeyName, MoveToPoints[0]);
		return EBTNodeResult::Succeeded;
	}

	Blackboard->SetValueAsVector(MoveToLocationKey.SelectedKeyName, MoveToPoints[PointsIter]);
	PointsIter = (PointsIter + 1) % (MoveToPoints.Num());
	return EBTNodeResult::Succeeded;
}


