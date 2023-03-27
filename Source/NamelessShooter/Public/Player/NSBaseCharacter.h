// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSBaseCharacter.generated.h"

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
	UNSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UNSWeaponComponent* WeaponComponent;

protected:

	virtual void BeginPlay() override;	

	void OnDeath();

	void OnHealthChanged(float Health, float DeltaHealth);

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetMovementDirection();

	UPROPERTY(BlueprintReadWrite)
	bool bReloadAnimMontageInProgress = false;

	UFUNCTION(BlueprintCallable)
	bool WantsLookAround() { return bWantsLookAround; }

	UFUNCTION(BlueprintCallable)
	ANSBaseWeapon* GetCurrentWeapon() const;
	
	void WeaponReload();

	bool IsDead();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage();
	
	void Shot();

	bool bWantsLookAround = false;

};
