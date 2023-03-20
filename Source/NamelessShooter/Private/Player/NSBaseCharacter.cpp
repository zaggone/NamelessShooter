// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/NSHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/NSWeaponComponent.h"

ANSBaseCharacter::ANSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UNSHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UNSWeaponComponent>("WeaponComponent");
}

void ANSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ANSBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ANSBaseCharacter::OnHealthChanged);
	
}

void ANSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// биндинг инпута
void ANSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveAlong", this, &ANSBaseCharacter::MoveAlong);
	PlayerInputComponent->BindAxis("MoveAcross", this, &ANSBaseCharacter::MoveAcross);
}

// колл бек функция на движение вдоль (кнопка W и S)
void ANSBaseCharacter::MoveAlong(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Amount);
}

// колл бек функция на движение поперек (кнопка A и D)
void ANSBaseCharacter::MoveAcross(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Amount);
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

// колл бек функция на смерть персонажа (когда погиб)
void ANSBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

// колл бек функция на изменение здоровья персонажа персонажа (когда погиб)
void ANSBaseCharacter::OnHealthChanged(float Health, float DeltaHealth)
{


}