// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/NSArrow.h"

ANSArrow::ANSArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	SetRootComponent(RootComponent);

	ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	ArrowMesh->SetupAttachment(GetRootComponent());
}

void ANSArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANSArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

