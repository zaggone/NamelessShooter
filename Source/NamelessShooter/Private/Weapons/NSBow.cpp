// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSBow.h"

ANSBow::ANSBow()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}
