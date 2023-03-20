// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNSHealthComponent;
class UNSWeaponComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UNSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UNSWeaponComponent* WeaponComponent;
	

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection();

	void OnDeath();

	void OnHealthChanged(float Health, float DeltaHealth);

	void StartLookingAround();
	void StopLookingAround();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float CameraLookoutVelocity = 5.0f;

private:

	bool bWantsLookAround = false;
	
	void MoveAlong(float Amount);
	void MoveAcross(float Amount);

	void LookAlong(float Amount);
	void LookAcross(float Amount);
};
