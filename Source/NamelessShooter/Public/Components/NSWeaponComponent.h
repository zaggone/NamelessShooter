// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NSWeaponComponent.generated.h"

class ANSBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NAMELESSSHOOTER_API UNSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UNSWeaponComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ANSBaseWeapon> CurrentWeaponClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TMap<TSubclassOf<ANSBaseWeapon>, FName> SocketsForWeapons;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SpawnWeapons();

	void AttachWeaponToSocket(ANSBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	
};
