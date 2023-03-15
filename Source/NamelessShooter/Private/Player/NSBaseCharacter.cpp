// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

ANSBaseCharacter::ANSBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ANSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveAlong", this, &ANSBaseCharacter::MoveAlong);
	PlayerInputComponent->BindAxis("MoveAcross", this, &ANSBaseCharacter::MoveAcross);

}

void ANSBaseCharacter::MoveAlong(float Amount)
{
	OnMovingAlong.Broadcast(Amount);
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ANSBaseCharacter::MoveAcross(float Amount)
{
	OnMovingAcross.Broadcast(Amount);
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

