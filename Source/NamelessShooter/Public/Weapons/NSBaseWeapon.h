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

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	APlayerController* GetPlayerController() const;
	FVector GetMuzzleWorldLocation() const;
private:

};
