// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSArrow.generated.h"

UCLASS()
class NAMELESSSHOOTER_API ANSArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	ANSArrow();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USceneComponent* SceneRootComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
