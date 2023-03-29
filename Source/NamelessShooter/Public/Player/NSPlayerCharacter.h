// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/NSBaseCharacter.h"
#include "NSPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class NAMELESSSHOOTER_API ANSPlayerCharacter : public ANSBaseCharacter
{
	GENERATED_BODY()
public:

	ANSPlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

protected:

	void StartLookingAround();

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StopLookingAround();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "5.0", ClampMax = "2000.0"))
	float CameraLookoutVelocity = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "1000.0", ClampMax = "10000.0"))
	float MaxCameraLookoutDistance = 2000.0f;

	APlayerController* GetPlayerController();

	FVector GetMouseLocationByCharacter();

private:

	void SetPawnRotationToMouse();
	void MoveAlong(float Amount);
	void MoveAcross(float Amount);

	void LookAlong(float Amount);
	void LookAcross(float Amount);

	FRotator NeedToRotating;

};
