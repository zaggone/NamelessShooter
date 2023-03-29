// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NSChangeMoveToTask.generated.h"

/**
 * 
 */
UCLASS()
class NAMELESSSHOOTER_API UNSChangeMoveToTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UNSChangeMoveToTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector MoveToLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector SelfActorKey;

	
};
