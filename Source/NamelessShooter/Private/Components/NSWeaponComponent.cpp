// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/NSWeaponComponent.h"
#include "Weapons/NSBaseWeapon.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);


UNSWeaponComponent::UNSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UNSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bArmed) 
	{
		check(CurrentWeaponClass); // не указан класс оружия (ненада так).. либо поставь bArmed в false
		SpawnWeapons();
	}
	
}

void UNSWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UNSWeaponComponent::SpawnWeapons()
{
	if (!GetOwner() || !bArmed) return;
	ACharacter* CurrentCharacter = Cast<ACharacter>(GetOwner());
	if (!CurrentCharacter || !GetWorld()) return;

	for (auto WeaponData : WeaponsData)
	{
		if (WeaponData.WeaponClass == CurrentWeaponClass)
		{
			CurrentWeapon = GetWorld()->SpawnActorDeferred<ANSBaseWeapon>(WeaponData.WeaponClass, FTransform(), GetOwner());
			CurrentWeapon->FinishSpawning(FTransform());
			AttachWeaponToSocket(CurrentWeapon, CurrentCharacter->GetMesh(), WeaponData.WeaponSocketName);
			return;
		}
	}
	UE_LOG(LogWeaponComponent, Error, TEXT("No Weapon To Spawn"));
}

void UNSWeaponComponent::AttachWeaponToSocket(ANSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent || !bArmed) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
void UNSWeaponComponent::Shot()
{
	if (!bArmed) return;
	CurrentWeapon->Shot();
}

void UNSWeaponComponent::Reload()
{
	if (!GetOwner() || !bArmed || !CurrentWeapon->MayReload()) return;
	const auto Character = Cast<ACharacter>(GetOwner());
	const auto CurrentWeaponData = WeaponsData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	Character->PlayAnimMontage(CurrentWeaponData->ReloadAnimMontage);
	CurrentWeapon->Reload();
}

TSubclassOf<UAnimInstance> UNSWeaponComponent::GetCurrentAnimInstanceClass()
{
	if (!GetOwner() || !bArmed) return TSubclassOf<UAnimInstance>();
	const auto CurrentWeaponData = WeaponsData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
	if(!CurrentWeaponData || !CurrentWeaponData->AnimInstanceClass)  checkNoEntry() // не найдено оружие или anim instance оружия
	return CurrentWeaponData->AnimInstanceClass;
}

