// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NSBaseWeapon.generated.h"

class UNSWeaponFXComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1200", ClampMax = "5000"))
	float TraceMaxDistance = 2000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "20", ClampMax = "200"))
	float DamageGiven = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1", ClampMax = "200"))
	int32 MaxBulletsInClipNum = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1", ClampMax = "10000"))
	int32 BulletsNum = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bHasFXComponent"))
	UNSWeaponFXComponent* WeaponFXComponent;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetMesh() const { return WeaponMesh; }
	
	virtual void Shot();
	
	virtual void Reload();

	virtual bool StartAim() { return false; }

	virtual bool StopAim() { return false; }

	virtual bool MayReload();

	virtual void SetProjectileSocketName(FName Name) { return; }

	virtual void OnOwnerDeath() { return; }

protected:
	
	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void GetHitResult(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	virtual void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	
	APlayerController* GetPlayerController() const;

	FVector GetMuzzleWorldLocation() const;

	void DecreaseAmmo();
	
	int32 CurrentBulletInClipNum;
	int32 CurrentBulletsNum;
	
};
