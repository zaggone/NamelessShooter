// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSBaseWeapon.generated.h"

UCLASS()
class NAMELESSSHOOTER_API ANSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ANSBaseWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USceneComponent* SceneRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName;

public:	
	virtual void Tick(float DeltaTime) override;

	USceneComponent* GetMesh() const { return WeaponMesh; }

	virtual void Shot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1200", ClampMax = "5000"))
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "20", ClampMax = "200"))
	float DamageGiven = 80;

	APlayerController* GetPlayerController() const;
	FVector GetMuzzleWorldLocation() const;

	void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);


private:

};
