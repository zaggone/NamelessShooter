// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NSAIController.generated.h"

class UNSAIPerceptionComponent;

UCLASS()
class NAMELESSSHOOTER_API ANSAIController : public AAIController
{
	GENERATED_BODY()
public:

	ANSAIController();
protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UNSAIPerceptionComponent* NSAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
private:
	AActor* GetFocusOnActor() const;
};
