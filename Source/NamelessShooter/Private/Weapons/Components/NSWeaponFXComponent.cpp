// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Components/NSWeaponFXComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Niagara/Public/NiagaraComponent.h"

UNSWeaponFXComponent::UNSWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UNSWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
	check(GetOwner());
	
}

void UNSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	if (!Hit.GetActor()) return;

	if (CharacterImpactFX) 
	{
		if (Hit.GetActor()->IsA<ACharacter>()) 
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CharacterImpactFX, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
		else 
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DefaultImpactFX, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
	}
	if (bSpawnDecal && DecalData.Material)
	{
		auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalData.Material, DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		if (DecalComponent)
		{
			DecalComponent->SetFadeScreenSize(0.0f);
			DecalComponent->SetFadeOut(DecalData.LifeTime, DecalData.FadeOutTime);
		}
	}
}

void UNSWeaponFXComponent::PlayFXAtLocation(const FVector& Location, const FVector& Normal, UNiagaraSystem* FX)
{
	if (!FX || !GetWorld()) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FX, Location, Normal.Rotation());
}

void UNSWeaponFXComponent::PlayMuzzleFX(USceneComponent* WeaponMesh, FName MuzzleSocketName)
{
	if (!bSpawnDecal || !MuzzleFX) return;
	UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMesh, MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

void UNSWeaponFXComponent::PlayTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld() || !GetOwner() || !bPlayTraceFX) return;
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);

	if (TraceFXComponent) 
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}


