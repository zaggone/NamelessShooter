// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSArrow.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

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

}

void ANSArrow::ThrowArrow(const FVector& ShotDirection)
{	
	check(MovementComponent);
	check(CollisionComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	MovementComponent->Activate();

	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + MovementComponent->Velocity , FColor::Red, false, 1.0f);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ANSArrow::OnComponentBeginOverlap);
}

void ANSArrow::BeginPlay()
{
	Super::BeginPlay();
	

}

void ANSArrow::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();
	if (OtherActor->IsA<ACharacter>()) 
	{
		OtherActor->TakeDamage(100.0f, FDamageEvent(), GetController(), GetOwner());
		Destroy();
	}
}

void ANSArrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();

	if (OtherActor->IsA<ACharacter>())
	{
		OtherActor->TakeDamage(100.0f, FDamageEvent(), GetController(), GetOwner());
		Destroy();
	}

}

AController* ANSArrow::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}



