// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "NSAIPerceptionComponent.generated.h"

UCLASS()
class NAMELESSSHOOTER_API UNSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	UNSAIPerceptionComponent();

	AActor* GetClosestEnemy() const;
protected:

	
};
