// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NSPlayerController.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"


void ANSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
}

void ANSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetPawnRotationToMouse();
}

void ANSPlayerController::SetPawnRotationToMouse()
{
	if (!GetWorld() || !GetPawn()) return;
	FVector MouseLocation;
	FVector MouseDirection;

	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	FVector MouseWorldLocation = FVector(MouseLocation.X, MouseLocation.Y, GetPawn()->GetActorLocation().Z);

	if ((MouseWorldLocation - GetPawn()->GetActorLocation()).Size() > 1.0f) 
	{
		NeedToRotating = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), MouseWorldLocation);
	}
	GetPawn()->SetActorRotation(NeedToRotating);
}
