// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSRevolver.h"
#include "Weapons/Components/NSWeaponFXComponent.h"

ANSRevolver::ANSRevolver()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

}
