// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/NSBaseWeapon.h"
#include "NSShotgun.generated.h"

/**
 * 
 */
UCLASS()
class NAMELESSSHOOTER_API ANSShotgun : public ANSBaseWeapon
{
	GENERATED_BODY()
public:
	ANSShotgun();

protected:
	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh;
	*/
public:
	//virtual USceneComponent* GetWeaponSceneComponent() const override { return WeaponMesh; }
};