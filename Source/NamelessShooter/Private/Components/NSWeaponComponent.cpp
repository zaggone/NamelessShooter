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
	SpawnWeapons();
	
}

void UNSWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
void UNSWeaponComponent::SpawnWeapons()
{
	ACharacter* CurrentCharacter = Cast<ACharacter>(GetOwner());
	if (!CurrentCharacter || !GetWorld()) return;

	for (auto OneWeaponData : SocketsForWeapons) 
	{
		if (OneWeaponData.Key == CurrentWeaponClass)
		{
			auto Weapon = GetWorld()->SpawnActor<ANSBaseWeapon>(OneWeaponData.Key);
			AttachWeaponToSocket(Weapon, CurrentCharacter->GetMesh(), OneWeaponData.Value);
			return;
		}
	}
	UE_LOG(LogWeaponComponent, Error, TEXT("No Weapon To Spawn"));
}

void UNSWeaponComponent::AttachWeaponToSocket(ANSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}