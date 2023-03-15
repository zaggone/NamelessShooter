// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovingHasDirection, float, Amount);

UCLASS()
class NAMELESSSHOOTER_API ANSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ANSBaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintAssignable)
	FOnMovingHasDirection OnMovingAcross;

	UPROPERTY(BlueprintAssignable)
	FOnMovingHasDirection OnMovingAlong;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveAlong(float Amount);
	void MoveAcross(float Amount);
};
