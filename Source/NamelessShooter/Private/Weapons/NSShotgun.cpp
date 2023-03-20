// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSShotgun.h"

ANSShotgun::ANSShotgun()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}
