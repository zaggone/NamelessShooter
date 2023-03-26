// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NSWeaponFXComponent.generated.h"

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAMELESSSHOOTER_API UNSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNSWeaponFXComponent();

protected:
	virtual void BeginPlay() override;

public:	

	void PlayImpactFX(const FHitResult& Hit);

	void PlayFXAtLocation(const FVector& Location, const FVector& Normal, UNiagaraSystem* FX);

	void PlayMuzzleFX(USceneComponent* WeaponMesh, FName MuzzleSocketName);

	void PlayTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	bool bPlayImpactFX = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bPlayImpactFX"))
	UNiagaraSystem* CharacterImpactFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bPlayImpactFX"))
	UNiagaraSystem* DefaultImpactFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	bool bPlayMuzzleFX = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bPlayMuzzleFX"))
	UNiagaraSystem* MuzzleFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	bool bSpawnDecal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bSpawnDecal"))
	FDecalData DecalData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	bool bPlayTraceFX = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bPlayTraceFX"))
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX", meta = (EditCondition = "bPlayTraceFX"))
	FString TraceTargetName = "TraceTarget";



};
