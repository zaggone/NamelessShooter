// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NSWeaponComponent.generated.h"

class ANSBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ANSBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UAnimInstance> AnimInstanceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool bNeedProjectileSocket = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "bNeedProjectileSocket"))
	FName ProjectileSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool bNeedAimAnimMontage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "bNeedAimAnimMontage"))
	UAnimMontage* AimAnimMontage;



};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NAMELESSSHOOTER_API UNSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UNSWeaponComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bArmed = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "bArmed"))
	TSubclassOf<ANSBaseWeapon> CurrentWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TArray<FWeaponData> WeaponsData;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Shot();
	
	void Reload();

	void OnOwnerDeath();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UAnimInstance> GetCurrentAnimInstanceClass();

	UFUNCTION(BlueprintCallable)
	void StartAim();

	void StopAim();

	ANSBaseWeapon* GetCurrentWeapon() const { return bArmed ? CurrentWeapon : nullptr; }

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	FWeaponData* GetCurrentWeaponData();


	ANSBaseWeapon* CurrentWeapon;

	void SpawnWeapons();
	
};
