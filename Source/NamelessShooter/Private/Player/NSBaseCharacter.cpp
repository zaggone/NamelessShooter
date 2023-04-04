// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NSBaseCharacter.h"
#include "Components/NSHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/NSWeaponComponent.h"
#include "Weapons/NSBaseWeapon.h"

ANSBaseCharacter::ANSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UNSHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UNSWeaponComponent>("WeaponComponent");

	bUseControllerRotationYaw = false;
}

void ANSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponComponent);
	check(HealthComponent);
	
	HealthComponent->OnDeath.AddUObject(this, &ANSBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ANSBaseCharacter::OnHealthChanged);

}

void ANSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// нахождение угла между скоростью и forward vector персонажа
float ANSBaseCharacter::GetMovementDirection()
{ 
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degreese = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degreese : Degreese * FMath::Sign(CrossProduct.Z);
}

bool ANSBaseCharacter::IsArmed()
{
	return WeaponComponent->IsArmed();
}

// колл бек функция на смерть персонажа (когда погиб)
void ANSBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	WeaponComponent->OnOwnerDeath();

	OnCharacterDeath();
}

// колл бек функция на изменение здоровья персонажа
void ANSBaseCharacter::OnHealthChanged(float Health, float DeltaHealth)
{
	if (DeltaHealth < 0) OnTakeDamage();
}

// на выстрел
void ANSBaseCharacter::Shot()
{
	UE_LOG(LogTemp, Error, TEXT("reload? %i"), bReloadAnimMontageInProgress)
	if (bReloadAnimMontageInProgress) return;
	WeaponComponent->Shot();
}

// перезарядка
void ANSBaseCharacter::WeaponReload()
{
	if (bReloadAnimMontageInProgress) return;
	WeaponComponent->Reload();
}
bool ANSBaseCharacter::IsDead()
{
	return HealthComponent->IsDead();
}
// геттер оружия
ANSBaseWeapon* ANSBaseCharacter::GetCurrentWeapon() const
{
	return WeaponComponent->GetCurrentWeapon(); 
}
