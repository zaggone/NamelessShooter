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

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetMesh() const { return WeaponMesh; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1200", ClampMax = "5000"))
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "20", ClampMax = "200"))
	float DamageGiven = 80;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1", ClampMax = "200"))
	int32 MaxBulletsInClipNum = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "1", ClampMax = "10000"))
	int32 BulletsNum = 50.0f;
	
	virtual void Shot();
	
	virtual void Reload();

	virtual bool StartAim() { return false; }

	virtual bool StopAim() { return false; }
	virtual bool MayReload();

	virtual void SetProjectileSocketName(FName Name) { return; }

protected:
	
	void GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void GetHitResult(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	virtual void MakeHit(FHitResult& HitResult, const FVector& TraceEnd);
	
	APlayerController* GetPlayerController() const;
	FVector GetMuzzleWorldLocation() const;

private:

	int32 CurrentBulletInClipNum;
	int32 CurrentBulletsNum;

};
