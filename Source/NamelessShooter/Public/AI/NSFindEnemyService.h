// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "NSFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class NAMELESSSHOOTER_API UNSFindEnemyService : public UBTService
{
	GENERATED_BODY()
public:
	UNSFindEnemyService();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
