// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSArrow.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNSWeaponFXComponent;

UCLASS()
class NAMELESSSHOOTER_API ANSArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	ANSArrow();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USceneComponent* SceneRootComponent;

	void ThrowArrow(const FVector& ShotDirection);

	void SetDamageGiven(float Damage) { DamageGiven = Damage; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bHasFXComponent"))
	UNSWeaponFXComponent* WeaponFXComponent;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:

	float DamageGiven;
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector CurrentShotDirection;
public:
	AController* GetController() const;
};
