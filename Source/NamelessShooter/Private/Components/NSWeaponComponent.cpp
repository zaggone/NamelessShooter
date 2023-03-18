// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/NSWeaponComponent.h"

UNSWeaponComponent::UNSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UNSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UNSWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

