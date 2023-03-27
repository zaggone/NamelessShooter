// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/NSBaseWeapon.h"
#include "NSShotgun.generated.h"

UCLASS()
class NAMELESSSHOOTER_API ANSShotgun : public ANSBaseWeapon
{
	GENERATED_BODY()
public:
	ANSShotgun();
protected:
	virtual void Shot() override;

	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 ShotsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpreadDegrees = 3.0f;
public:

};
