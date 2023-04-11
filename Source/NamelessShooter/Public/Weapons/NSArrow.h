// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSArrow.generated.h"

class UCapsuleComponent;
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

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitAtCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHitDefault();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:

	float DamageGiven;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	FVector CurrentShotDirection;

public:
	AController* GetController() const;

	void OnOwnerDeath();

	void ClearCollision();
};
