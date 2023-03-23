// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSBow.h"

ANSBow::ANSBow()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}

bool ANSBow::StartAim()
{
	CanShot = true;
	return true;
}

bool ANSBow::StopAim()
{
	CanShot = false;
	return true;
}

void ANSBow::Shot()
{
	UE_LOG(LogTemp, Error, TEXT("bow start shot"));
	if (!CanShot) return;
	UE_LOG(LogTemp, Error, TEXT("bow shot"));
	Super::Shot();
}
