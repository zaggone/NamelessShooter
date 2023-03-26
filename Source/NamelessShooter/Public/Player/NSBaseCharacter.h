// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNSHealthComponent;
class UNSWeaponComponent;
class ANSBaseWeapon;

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

	void OnDeath();

	void OnHealthChanged(float Health, float DeltaHealth);

	void StartLookingAround();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection();

	void StopLookingAround();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "5.0", ClampMax = "2000.0"))
	float CameraLookoutVelocity = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "1000.0", ClampMax = "10000.0"))
	float MaxCameraLookoutDistance = 2000.0f;

	void SetPawnRotationToMouse();

	APlayerController* GetPlayerController();

	FVector GetMouseLocationByCharacter();

	UPROPERTY(BlueprintReadWrite)
	bool bReloadAnimMontageInProgress = false;

	UFUNCTION(BlueprintCallable)
	bool WantsLookAround() { return bWantsLookAround; }

	UFUNCTION(BlueprintCallable)
	ANSBaseWeapon* GetCurrentWeapon() const;
	
	void WeaponReload();

	bool IsDead();

private:

	bool bWantsLookAround = false;
	
	void MoveAlong(float Amount);
	void MoveAcross(float Amount);

	void LookAlong(float Amount);
	void LookAcross(float Amount);

	void Shot();

	FRotator NeedToRotating;
};
