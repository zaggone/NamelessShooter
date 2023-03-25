// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/NSBow.h"
#include "Weapons/NSArrow.h"
#include "NSUtils.h"
#include "Player/NSBaseCharacter.h"
#include "DrawDebugHelpers.h"

ANSBow::ANSBow()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void ANSBow::BeginPlay()
{
	Super::BeginPlay();
	SpawnArrow();
}

void ANSBow::MakeHit(FHitResult& HitResult, const FVector& TraceEnd)
{
	UE_LOG(LogTemp, Error, TEXT("7"));
	if (!CurrentArrow || !GetOwner() || !GetWorld()) return;

	const auto Character = Cast<ANSBaseCharacter>(GetOwner());
	if (!Character) return;
	const FVector EndPoint = GetOwner()->GetActorForwardVector() * TraceMaxDistance;
	const FVector Direction = (Character->GetMouseLocationByCharacter() - CurrentArrow->GetActorLocation()).GetSafeNormal();

	//DrawDebugLine(GetWorld(), CurrentArrow->GetActorLocation(), Direction * TraceMaxDistance, FColor::Red, false, 1.0f);

	CurrentArrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentArrow->ThrowArrow(Direction);
	CurrentArrow = nullptr;

}

void ANSBow::Tick(float DeltaTime)
{

}

bool ANSBow::StartAim()
{

	bAim = true;
	return true;
}

bool ANSBow::StopAim()
{

	bAim = false;
	return true;
}

void ANSBow::SpawnArrow()
{
	if (!GetWorld() || !GetOwner() || CurrentArrow) return;
	
	ACharacter* CurrentCharacter = Cast<ANSBaseCharacter>(GetOwner());
	if (!CurrentCharacter) return;

	CurrentArrow = GetWorld()->SpawnActorDeferred<ANSArrow>(ArrowClass, FTransform(), GetOwner());

	CurrentArrow->FinishSpawning(FTransform());
	NSUtils::AttachToSocket(CurrentArrow, CurrentCharacter->GetMesh(), ArrowSocketName);
}

void ANSBow::Shot()
{
	if (!bAim || !CurrentArrow) return;
	Super::Shot();
}

void ANSBow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentArrow)
	{
		CurrentArrow->Destroy();
		CurrentArrow = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}
