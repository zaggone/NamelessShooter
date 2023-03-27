// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/NSBaseWeapon.h"
#include "NSBow.generated.h"

class ANSArrow;
UCLASS()
class NAMELESSSHOOTER_API ANSBow : public ANSBaseWeapon
{
	GENERATED_BODY()

public:
	ANSBow();

protected:
	
	virtual bool StartAim() override;

	virtual bool StopAim() override;

	virtual void BeginPlay() override;

	virtual void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ANSArrow> ArrowClass;

	virtual void SetProjectileSocketName(FName Name) override { ArrowSocketName = Name; };
	
	UFUNCTION(BlueprintCallable)
	void SpawnArrow();

	virtual void Shot() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	virtual void OnOwnerDeath() override;

private:

	ANSArrow* CurrentArrow = nullptr;

	bool bAim = false;

	FName ArrowSocketName;

};
