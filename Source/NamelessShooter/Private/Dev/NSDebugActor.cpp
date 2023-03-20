// Fill out your copyright notice in the Description page of Project Settings.

#include "Dev/NSDebugActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ANSDebugActor::ANSDebugActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ANSDebugActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANSDebugActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);
}

