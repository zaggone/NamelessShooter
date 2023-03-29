// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NSAIController.h"
#include "AI/NSAICharacter.h"
#include "AI/NSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ANSAIController::ANSAIController()
{
	NSAIPerceptionComponent = CreateDefaultSubobject<UNSAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*NSAIPerceptionComponent);
}

void ANSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AIChar = Cast<ANSAICharacter>(InPawn);
	if (AIChar) 
	{
		RunBehaviorTree(AIChar->BehaviorTreeAsset);
	}
}
void ANSAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}
AActor* ANSAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}