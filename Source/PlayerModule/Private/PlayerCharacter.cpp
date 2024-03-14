// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
}

void APlayerCharacter::MoveForward(float inputVec)
{
	FVector forwardDirection = GetActorForwardVector();
	AddMovementInput(forwardDirection, inputVec);
}

void APlayerCharacter::MoveRight(float inputVec)
{
	FVector rightDirection = GetActorRightVector();
	AddMovementInput(rightDirection, inputVec);
}

void APlayerCharacter::Turn(float inputVec)
{
	AddControllerYawInput(inputVec);
}

void APlayerCharacter::LookUp(float inputVec)
{
	AddControllerPitchInput(inputVec);
}
