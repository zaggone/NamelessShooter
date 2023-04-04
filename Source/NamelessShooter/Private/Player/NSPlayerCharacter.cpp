// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/NSWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"

ANSPlayerCharacter::ANSPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->SocketOffset.Z = 1000.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void ANSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetPawnRotationToMouse();
}

// биндинг инпута
void ANSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveAlong", this, &ANSPlayerCharacter::MoveAlong);
	PlayerInputComponent->BindAxis("MoveAcross", this, &ANSPlayerCharacter::MoveAcross);
	PlayerInputComponent->BindAxis("LookAlong", this, &ANSPlayerCharacter::LookAlong);
	PlayerInputComponent->BindAxis("LookAcross", this, &ANSPlayerCharacter::LookAcross);
	PlayerInputComponent->BindAction("WantsToLookAround", IE_Pressed, this, &ANSPlayerCharacter::StartLookingAround);
	PlayerInputComponent->BindAction("WantsToLookAround", IE_Released, this, &ANSPlayerCharacter::StopLookingAround);
	PlayerInputComponent->BindAction("Shot", IE_Pressed, this, &ANSPlayerCharacter::Shot);
	PlayerInputComponent->BindAction("WeaponReload", IE_Pressed, this, &ANSPlayerCharacter::WeaponReload);
}

// колл бек функция на движение вдоль (кнопка W и S)
void ANSPlayerCharacter::MoveAlong(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Amount);
}

// колл бек функция на движение поперек (кнопка A и D)
void ANSPlayerCharacter::MoveAcross(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Amount);
}

// вращаем перса к мышке 
void ANSPlayerCharacter::SetPawnRotationToMouse()
{
	if (!GetWorld()) return;

	const auto MouseLocationByCharacter = GetMouseLocationByCharacter();
	const auto ActorXYVec = FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f);
	const auto MouseXYVec = FVector(MouseLocationByCharacter.X, MouseLocationByCharacter.Y, 0.0f);
	//(если мышка ближе 120 см к персу то игнорируем)
	if ((MouseXYVec - ActorXYVec).Size() > 70.0f)
	{
		NeedToRotating = UKismetMathLibrary::FindLookAtRotation(ActorXYVec, MouseXYVec);
	}

	SetActorRotation(FRotator(GetActorRotation().Pitch, NeedToRotating.Yaw, GetActorRotation().Roll));
	//DrawDebugLine(GetWorld(), GetActorLocation(), MouseLocationByCharacter, FColor::Red, false, 0.2f);
}
// геттеер player controller
APlayerController* ANSPlayerCharacter::GetPlayerController()
{
	return Cast<APlayerController>(Controller);
}
// получаем корды мышки в мире относительно персонажа (чутка костыльно)
FVector ANSPlayerCharacter::GetMouseLocationByCharacter()
{
	const auto PlayerController = GetPlayerController();
	if (!PlayerController) return FVector();

	FVector MouseLocation;
	FVector MouseDirection;

	PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	const auto CurrentCos = FVector::DotProduct(FVector(0.0f, 0.0f, -1.0f), MouseDirection);
	const auto CurrentMouseWorldLocation = MouseLocation + MouseDirection * ((SpringArmComponent->SocketOffset.Z - 20.0f) / CurrentCos);

	return CurrentMouseWorldLocation;
}
// колл бек на начало обзора окружения
void ANSPlayerCharacter::StartLookingAround()
{
	bWantsLookAround = true;

	if (bReloadAnimMontageInProgress) return;
	WeaponComponent->StartAim();
}

// колл бек на конец обзора окружения
void ANSPlayerCharacter::StopLookingAround()
{
	bWantsLookAround = false;
	SpringArmComponent->SocketOffset.Y = 0;
	SpringArmComponent->SocketOffset.X = 0;

	//if (bReloadAnimMontageInProgress) return;
	WeaponComponent->StopAim();
}

// обзор по оси y
void ANSPlayerCharacter::LookAlong(float Amount)
{
	if (!bWantsLookAround || Amount == 0) return;

	// если больше заданной дистанции то игнорим
	if (FMath::Abs(SpringArmComponent->SocketOffset.Y + CameraLookoutVelocity * Amount) > MaxCameraLookoutDistance)
	{
		return;
	}
	SpringArmComponent->SocketOffset.Y += CameraLookoutVelocity * Amount;
}

// обзор по оси x
void ANSPlayerCharacter::LookAcross(float Amount)
{
	if (!bWantsLookAround || Amount == 0) return;

	// если больше заданной дистанции то игнорим
	if (FMath::Abs(SpringArmComponent->SocketOffset.X + CameraLookoutVelocity * Amount) > MaxCameraLookoutDistance)
	{
		return;
	}
	SpringArmComponent->SocketOffset.X += CameraLookoutVelocity * Amount;
}