// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSBaseWeapon.h"
#include "GameFramework/Character.h"

ANSBaseWeapon::ANSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	SetRootComponent(SceneRootComponent);
}

void ANSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANSBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANSBaseWeapon::Shot()
{
	UE_LOG(LogTemp, Error, TEXT("shot"));
}

bool ANSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto STUCharacter = Cast<ACharacter>(GetOwner());
	if (!STUCharacter) return false;

	if (STUCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if (!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}


	return true;
}

APlayerController* ANSBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

FVector ANSBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
