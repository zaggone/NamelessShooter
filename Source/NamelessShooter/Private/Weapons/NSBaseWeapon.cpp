// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSBaseWeapon.h"

ANSBaseWeapon::ANSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANSBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

