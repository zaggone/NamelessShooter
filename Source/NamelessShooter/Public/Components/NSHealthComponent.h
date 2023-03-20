// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAMELESSSHOOTER_API UNSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UNSHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() { return Health <= 0.0f; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	bool IsHealthFull() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"), Category = "Health")
	float MaxHealth = 100.0f;

	virtual void BeginPlay() override;

private:

	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void SetHealth(float NewHealth);
	AActor* ComponentOwner;

};
