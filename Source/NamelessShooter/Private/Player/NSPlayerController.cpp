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
	SetPawnRotationToMouse();
}

// делаем перса направленным к курсору
void ANSPlayerController::SetPawnRotationToMouse()
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	FVector MouseLocation;
	FVector MouseDirection;

	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	FRotator NeedToRotating = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), FVector(MouseLocation.X, MouseLocation.Y, GetPawn()->GetActorLocation().Z));

	GetPawn()->SetActorRotation(NeedToRotating);
}
