// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSArrow.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Weapons/Components/NSWeaponFXComponent.h"
#include "Player/NSBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ANSArrow::ANSArrow()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	SetRootComponent(SceneRootComponent);

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	CollisionComponent->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->bAutoActivate = false;
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	ArrowMesh->SetupAttachment(GetRootComponent());

	WeaponFXComponent = CreateDefaultSubobject<UNSWeaponFXComponent>("WeaponFXComponent");
	WeaponFXComponent->bSpawnDecal = false;
	WeaponFXComponent->bPlayMuzzleFX = false;
	WeaponFXComponent->bPlayTraceFX = false;
}

void ANSArrow::BeginPlay()
{
	Super::BeginPlay();
}

// когда выстреливаем из лука
void ANSArrow::ThrowArrow(const FVector& ShotDirection)
{	
	check(MovementComponent);
	check(CollisionComponent);
	CurrentShotDirection = ShotDirection;
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	MovementComponent->Activate();

	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + MovementComponent->Velocity , FColor::Red, false, 1.0f);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANSArrow::OnComponentBeginOverlap);
}

// колл бек на overlap
void ANSArrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();

	if (OtherActor->IsA<ANSBaseCharacter>())
	{
		auto Character = Cast<ANSBaseCharacter>(OtherActor);

		Character->TakeDamage(DamageGiven, FDamageEvent(), GetController(), GetOwner());
		WeaponFXComponent->PlayFXAtLocation(CollisionComponent->GetComponentLocation(), -CurrentShotDirection, WeaponFXComponent->CharacterImpactFX);
		
		if (Character->IsDead()) Character->GetMesh()->AddImpulse(CurrentShotDirection * 5000, "Pelvis", true);
		else Character->GetCharacterMovement()->AddImpulse(CurrentShotDirection * 1000, true);
		Destroy();
		return;
	}

	WeaponFXComponent->PlayFXAtLocation(CollisionComponent->GetComponentLocation(), -CurrentShotDirection, WeaponFXComponent->DefaultImpactFX);
	SetOwner(nullptr);
	SetLifeSpan(20.0f);
}
// геттер контроллера
AController* ANSArrow::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}



