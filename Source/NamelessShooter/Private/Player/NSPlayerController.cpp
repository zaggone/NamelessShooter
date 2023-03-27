// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/NSPlayerController.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"

void ANSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	//bShowMouseCursor = true;
}

void ANSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
