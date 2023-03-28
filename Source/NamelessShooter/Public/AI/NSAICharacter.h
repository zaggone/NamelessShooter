// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/NSBaseCharacter.h"
#include "NSAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class NAMELESSSHOOTER_API ANSAICharacter : public ANSBaseCharacter
{
	GENERATED_BODY()

public:

	ANSAICharacter();

	virtual void OnDeath() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
};
