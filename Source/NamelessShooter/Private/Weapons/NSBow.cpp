// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSBow.h"
#include "Weapons/NSArrow.h"
#include "NSUtils.h"
#include "Player/NSBaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "Weapons/Components/NSWeaponFXComponent.h"

ANSBow::ANSBow()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	WeaponFXComponent->bPlayImpactFX = false;
	WeaponFXComponent->bSpawnDecal = false;
	WeaponFXComponent->bPlayTraceFX = false;
	WeaponFXComponent->bPlayMuzzleFX = false;
}

void ANSBow::BeginPlay()
{
	Super::BeginPlay();
	SpawnArrow();
}

void ANSBow::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!CurrentArrow || !GetOwner() || !GetWorld()) return;

	const auto Character = Cast<ANSBaseCharacter>(GetOwner());
	if (!Character) return;

	const FVector Direction = (TraceEnd - TraceStart).GetSafeNormal();

	CurrentArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentArrow->ThrowArrow(Direction);
	CurrentArrow = nullptr;
}

bool ANSBow::StartAim()
{
	if (!GetOwner() || !CurrentArrow) return false;
	bAim = true;
	return true;
}

bool ANSBow::StopAim()
{
	if (!GetOwner() || !CurrentArrow) return false;
	bAim = false;
	return true;
}

// спавнит стрелу (вызывается в ABP_BowEquip на ивент)
void ANSBow::SpawnArrow()
{
	if (!GetWorld() || !GetOwner() || CurrentArrow) return;
	
	ACharacter* CurrentCharacter = Cast<ANSBaseCharacter>(GetOwner());
	if (!CurrentCharacter) return;

	CurrentArrow = GetWorld()->SpawnActorDeferred<ANSArrow>(ArrowClass, FTransform(), GetOwner());
	CurrentArrow->SetDamageGiven(DamageGiven);
	CurrentArrow->FinishSpawning(FTransform());
	NSUtils::AttachToSocket(CurrentArrow, CurrentCharacter->GetMesh(), ArrowSocketName);
}

// переопределяем для добавляения исключений
void ANSBow::Shot()
{
	if (!bAim || !CurrentArrow) return;
	Super::Shot();
}
// чистка указателя на стрелу 
void ANSBow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentArrow)
	{
		CurrentArrow->Destroy();
		CurrentArrow = nullptr;
	} 
	else CurrentArrow = nullptr;
	
	Super::EndPlay(EndPlayReason);
}

void ANSBow::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if (!CurrentArrow || !GetOwner() || !GetWorld()) return;

	const auto Character = Cast<ANSBaseCharacter>(GetOwner());
	if (!Character) return;

	TraceStart = CurrentArrow->GetActorLocation();
	TraceEnd = Character->GetMouseLocationByCharacter();
}

void ANSBow::OnOwnerDeath()
{
	CurrentArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentArrow->Destroy();
}
