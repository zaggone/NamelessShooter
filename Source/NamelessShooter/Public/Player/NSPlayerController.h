// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NSPlayerController.generated.h"

UCLASS()
class NAMELESSSHOOTER_API ANSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	void SetPawnRotationToMouse();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pawn Settings")
	bool bRotatingPawnToMouse = true;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FRotator NeedToRotating;
};
