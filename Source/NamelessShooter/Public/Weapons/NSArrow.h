// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSArrow.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

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

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	AController* GetController() const;
};
