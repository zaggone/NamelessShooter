// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Player/NSBaseCharacter.h"
#include "Engine/World.h"

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
	FHitResult HitResult;
	FVector TraceStart;
	FVector TraceEnd;

	GetTraceData(TraceStart, TraceEnd);
	MakeHit(HitResult, TraceStart, TraceEnd);
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

void ANSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{	
	if (!GetOwner()) return;
	FVector ViewLocation;
	FRotator ViewRotation;

	TraceStart = GetMuzzleWorldLocation();
	const FVector ShootDirection = GetOwner()->GetActorForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	
}

void ANSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

	if (HitResult.bBlockingHit) 
	{	
		if(HitResult.GetActor()->IsA<ANSBaseCharacter>()) 
		{
			UE_LOG(LogTemp, Error, TEXT("character"));
			auto Character = Cast<ANSBaseCharacter>(HitResult.GetActor());
			Character->TakeDamage(DamageGiven, FDamageEvent(), GetPlayerController(), GetOwner());
		}
	}
}
