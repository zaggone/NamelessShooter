// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/NSPlayerController.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void ANSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
}

void ANSPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bRotatingPawnToMouse) SetPawnRotationToMouse();
}

//устанавливаем направление перса к мышке 
void ANSPlayerController::SetPawnRotationToMouse()
{
	if (!GetWorld() || !GetPawn()) return;
	FVector MouseLocation;
	FVector MouseDirection;
	
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	auto CurrentMouseLocation = MouseLocation + (-MouseDirection * (MouseLocation.Z / MouseDirection.Z));
	CurrentMouseLocation = FVector(CurrentMouseLocation.X, CurrentMouseLocation.Y, GetPawn()->GetActorLocation().Z + 50);

	//(если мышка ближе 120 см игнорируем)
	if ((CurrentMouseLocation - GetPawn()->GetActorLocation()).Size() > 120.0f)
	{
		NeedToRotating = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), CurrentMouseLocation);
	}
	
	GetPawn()->SetActorRotation(FRotator(GetPawn()->GetActorRotation().Pitch, NeedToRotating.Yaw, GetPawn()->GetActorRotation().Roll));
	DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), CurrentMouseLocation, FColor::Red, false, 0.2f);
}
