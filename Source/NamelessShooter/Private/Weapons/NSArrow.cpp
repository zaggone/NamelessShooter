// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSArrow.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Weapons/Components/NSWeaponFXComponent.h"
#include "Player/NSBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Delegates/DelegateBase.h"
#include "Components/CapsuleComponent.h"

ANSArrow::ANSArrow()
{
	PrimaryActorTick.bCanEverTick = false;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->bAutoActivate = false;
	MovementComponent->InitialSpeed = 3000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	ArrowMesh->SetupAttachment(GetRootComponent());
	ArrowMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ArrowMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ArrowMesh->bReturnMaterialOnMove = true;
	SetRootComponent(ArrowMesh);

	WeaponFXComponent = CreateDefaultSubobject<UNSWeaponFXComponent>("WeaponFXComponent");
	WeaponFXComponent->bSpawnDecal = false;
	WeaponFXComponent->bPlayMuzzleFX = false;
	WeaponFXComponent->bPlayTraceFX = false;
}

void ANSArrow::BeginPlay()
{
	Super::BeginPlay();
	ArrowMesh->IgnoreActorWhenMoving(GetOwner(), true);
}

// когда выстреливаем из лука
void ANSArrow::ThrowArrow(const FVector& ShotDirection)
{	
	check(MovementComponent);
	check(ArrowMesh);
	CurrentShotDirection = ShotDirection;
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	MovementComponent->Activate();

	ArrowMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANSArrow::OnComponentBeginOverlap);

	ArrowMesh->OnComponentHit.AddDynamic(this, &ANSArrow::OnComponentHit);
	SetLifeSpan(20.0f);
}

// колл бек на hit
void ANSArrow::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("!!!"));

	if (!GetWorld() || !GetOwner()) return;

	auto Character = Cast<ANSBaseCharacter>(OtherActor);

	if (Character)
	{
		if (Character == Cast<ANSBaseCharacter>(GetOwner())) return;

		MovementComponent->StopMovementImmediately();

		if (Cast<ANSBaseCharacter>(GetOwner()) == Character) return;

		Character->TakeDamage(DamageGiven, FDamageEvent(), GetController(), GetOwner());
		WeaponFXComponent->PlayFXAtLocation(Hit.ImpactPoint, -CurrentShotDirection, WeaponFXComponent->CharacterImpactFX);

		if (Character->IsDead()) Character->GetMesh()->AddImpulse(CurrentShotDirection * 5000, "Pelvis", true);
		else Character->GetCharacterMovement()->AddImpulse(CurrentShotDirection * 1000, true);
		OnHitAtCharacter();
		SetOwner(nullptr);
		Destroy();
		return;
	}

	MovementComponent->StopMovementImmediately();

	WeaponFXComponent->PlayFXAtLocation(Hit.ImpactPoint, -CurrentShotDirection, WeaponFXComponent->DefaultImpactFX);
	SetOwner(nullptr);
	OnHitDefault();

	FTimerHandle ArrowTimerHandle;
	ClearCollision();
	//GetWorld()->GetTimerManager().SetTimer(ArrowTimerHandle, this, &ANSArrow::ClearCollision, 1.0f, false);
}


// геттер контроллера
AController* ANSArrow::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void ANSArrow::OnOwnerDeath()
{
	ClearCollision();
	SetOwner(nullptr);
	Destroy();
}

void ANSArrow::ClearCollision()
{
	ArrowMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ArrowMesh->OnComponentHit.Clear();
}



