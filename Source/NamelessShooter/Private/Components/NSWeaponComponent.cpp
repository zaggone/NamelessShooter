// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/NSWeaponComponent.h"
#include "Weapons/NSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/NSBaseCharacter.h"
#include "NSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);


UNSWeaponComponent::UNSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UNSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GetOwner())
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
// спавн оружия 
void UNSWeaponComponent::SpawnWeapons()
{
	if (!bArmed || CurrentWeapon) return;
	const auto CurrentCharacter = Cast<ACharacter>(GetOwner());
	if (!CurrentCharacter || !GetWorld()) return;

	for (auto WeaponData : WeaponsData)
	{
		if (WeaponData.WeaponClass == CurrentWeaponClass)
		{
			CurrentWeapon = GetWorld()->SpawnActorDeferred<ANSBaseWeapon>(WeaponData.WeaponClass, FTransform(), GetOwner());

			if (WeaponData.bNeedProjectileSocket) CurrentWeapon->SetProjectileSocketName(WeaponData.ProjectileSocketName);
			CurrentWeapon->FinishSpawning(FTransform());
			NSUtils::AttachToSocket(CurrentWeapon, CurrentCharacter->GetMesh(), WeaponData.WeaponSocketName);
			return;
		}
	}
	UE_LOG(LogWeaponComponent, Error, TEXT("No Weapon To Spawn"));
}

void UNSWeaponComponent::Shot()
{
	if (!bArmed || !CurrentWeapon) return;
	CurrentWeapon->Shot();
}

void UNSWeaponComponent::Reload()
{
	if (!bArmed || !CurrentWeapon ||!CurrentWeapon->MayReload()) return;
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	StopAim();
	const auto CurrentWeaponData = GetCurrentWeaponData();

	if (!CurrentWeaponData->ReloadAnimMontage) checkNoEntry();
	Character->PlayAnimMontage(CurrentWeaponData->ReloadAnimMontage);
	CurrentWeapon->Reload();
	StopAim();
}
// геттер анимационного блюпринта для конкретного оружия
TSubclassOf<UAnimInstance> UNSWeaponComponent::GetCurrentAnimInstanceClass()
{
	if (!bArmed || !CurrentWeapon) checkNoEntry(); // какого хера функция тогда вообще была вызвана а?
	const auto CurrentWeaponData = GetCurrentWeaponData();
	if (!CurrentWeaponData || !CurrentWeaponData->AnimInstanceClass)  checkNoEntry(); // не найдено оружие или anim instance оружия
	return CurrentWeaponData->AnimInstanceClass;
}

void UNSWeaponComponent::StartAim()
{ 
	if (!CurrentWeapon) return;
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetCurrentMontage()) return;
	if (CurrentWeapon->StartAim()) 
	{
		const auto CurrentWeaponData = GetCurrentWeaponData();
		if (!CurrentWeaponData->bNeedAimAnimMontage || !CurrentWeaponData->AimAnimMontage) checkNoEntry(); // скорее всего не установлен AimAnimMontage
		Character->PlayAnimMontage(CurrentWeaponData->AimAnimMontage);
		Character->GetCharacterMovement()->MaxWalkSpeed = 400;
	}
}

void UNSWeaponComponent::StopAim()
{
	if (!CurrentWeapon) return;

	if(CurrentWeapon->StopAim()) 
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (!Character) return;
		const auto CurrentWeaponData = GetCurrentWeaponData();
		if (!CurrentWeaponData->bNeedAimAnimMontage || !CurrentWeaponData->AimAnimMontage) checkNoEntry(); // скорее всего не установлен AimAnimMontage
		Character->StopAnimMontage(CurrentWeaponData->AimAnimMontage);
		Character->GetCharacterMovement()->MaxWalkSpeed = 500;
	}
}

FWeaponData* UNSWeaponComponent::GetCurrentWeaponData()
{
	if (!CurrentWeapon || WeaponsData.Num() == 0) checkNoEntry(); // чета с оружием или WeaponData-ой :-|
	return WeaponsData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
}
// чистка указателя на оружия;
void UNSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentWeapon) 
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

void UNSWeaponComponent::OnOwnerDeath()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->OnOwnerDeath();
}
