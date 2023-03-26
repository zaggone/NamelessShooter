// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSShotgun.h"
#include "Weapons/Components/NSWeaponFXComponent.h"

ANSShotgun::ANSShotgun()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	MaxBulletsInClipNum = 8;
}

void ANSShotgun::Shot()
{
	if (!GetOwner() || !GetWorld() || CurrentBulletInClipNum == 0) return;

	for (int32 i = CurrentBulletInClipNum >= ShotsNum ? ShotsNum : CurrentBulletInClipNum; i > 0; i--) 
	{
		Super::Shot();
	}
}

void ANSShotgun::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if (!GetOwner() || !GetWorld()) return;

	TraceStart = GetMuzzleWorldLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpreadDegrees);
	const FVector ShootDirection = FMath::VRandCone(GetOwner()->GetActorForwardVector(), HalfRad);
	TraceEnd = GetOwner()->GetActorLocation() + ShootDirection * TraceMaxDistance;
}
