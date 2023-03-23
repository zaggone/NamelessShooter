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
	CurrentBulletsNum = BulletsNum;
	Reload();
}

void ANSBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// вызывается когда выстреливаем
void ANSBaseWeapon::Shot()
{
	if (!GetOwner() || !GetWorld()) return;
	FHitResult HitResult;
	FVector TraceStart;
	FVector TraceEnd;

	GetTraceData(TraceStart, TraceEnd);

	MakeHit(HitResult, TraceStart, TraceEnd);
}

// геттер player controller
APlayerController* ANSBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

// получаем координаты дула оружия
FVector ANSBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// метод получения инфы для трейса (начало / конец)
void ANSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{	
	if (!GetOwner()) return;
	FVector ViewLocation;
	FRotator ViewRotation;

	TraceStart = GetMuzzleWorldLocation();
	const FVector ShootDirection = GetOwner()->GetActorForwardVector();
	TraceEnd = GetOwner()->GetActorLocation() + ShootDirection * TraceMaxDistance;
}
// делаем line trace и получаем инфу о попадании, в зависимости от того куда попали наносим урон.
void ANSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld() || CurrentBulletInClipNum == 0) return;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);

	if (HitResult.bBlockingHit) 
	{	
		if(HitResult.GetActor()->IsA<ANSBaseCharacter>()) 
		{
			auto Character = Cast<ANSBaseCharacter>(HitResult.GetActor());
			Character->TakeDamage(DamageGiven, FDamageEvent(), GetPlayerController(), GetOwner());
		}
	}

	CurrentBulletInClipNum--;
	if (CurrentBulletInClipNum == 0 && MayReload()) 
	{
		auto Character = Cast<ANSBaseCharacter>(GetOwner());
		Character->WeaponReload();
	}
	//UE_LOG(LogTemp, Error, TEXT("all %i   in clip %i   max in clip %i"), CurrentBulletsNum, CurrentBulletInClipNum, MaxBulletsInClipNum);
}

// перезарядка оружия
void ANSBaseWeapon::Reload()
{
	if (!MayReload()) return;

	if (CurrentBulletsNum - (MaxBulletsInClipNum - CurrentBulletInClipNum) >= 0)
	{	
		CurrentBulletsNum = CurrentBulletsNum - (MaxBulletsInClipNum - CurrentBulletInClipNum);
		CurrentBulletInClipNum = MaxBulletsInClipNum;
	}
	else 
	{
		CurrentBulletInClipNum = CurrentBulletsNum;
		CurrentBulletsNum = 0;
	}
	UE_LOG(LogTemp, Error, TEXT("all %i   in clip %i   max in clip %i"), CurrentBulletsNum, CurrentBulletInClipNum, MaxBulletsInClipNum);
}

bool ANSBaseWeapon::MayReload()
{
	return !(!GetOwner() || CurrentBulletsNum <= 0 || CurrentBulletInClipNum == MaxBulletsInClipNum);
}
