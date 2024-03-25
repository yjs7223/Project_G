// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerWidget.h"
#include "GameFramework/PlayerInput.h"

APlayerCharacter::APlayerCharacter()
{
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;

	weaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponActor"));
	weaponActor->SetupAttachment(RootComponent);
	//weaponActor->CreateChildActor()

	inputVector = FVector::ZeroVector;
	bFire = false;
	jumpCount = 2;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		if (PlayerWidget)
		{
			PlayerWidget->RemoveFromViewport();
		}

		PlayerWidget = CreateWidget<UPlayerWidget>(Cast<APlayerController>(GetController()), PlayerWidgetClass);
		if (PlayerWidget) {
			PlayerWidget->AddToViewport();
		}
	}

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Moving();
	SetWeaponRotation();
	CheckHoldingKey();
	//GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::SanitizeFloat(weaponHoldingtime));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("SwapWeapon", IE_Pressed, this, &APlayerCharacter::StartSwapWeapon);
	PlayerInputComponent->BindAction("SwapWeapon", IE_Released, this, &APlayerCharacter::StopSwapWeapon);

	PlayerInputComponent->BindAction("SwapElement", IE_Pressed, this, &APlayerCharacter::StartSwapElement);
	PlayerInputComponent->BindAction("SwapElement", IE_Released, this, &APlayerCharacter::StopSwapElement);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
}

void APlayerCharacter::Moving()
{
	if (inputVector != FVector::ZeroVector)
	{
		FVector MoveDirection = FVector::ZeroVector;
		MoveDirection = GetController()->GetControlRotation().RotateVector(inputVector);
		MoveDirection.Normalize();
		MoveDirection *= GetCharacterMovement()->MaxWalkSpeed;
		
		AddMovementInput(MoveDirection);
	}
}

void APlayerCharacter::MoveForward(float input)
{
	/*FVector forwardDirection = GetActorForwardVector();
	AddMovementInput(forwardDirection, input);*/

	inputVector.X = input;
}

void APlayerCharacter::MoveRight(float input)
{
	/*FVector rightDirection = GetActorRightVector();
	AddMovementInput(rightDirection, input);*/

	inputVector.Y = input;
}

void APlayerCharacter::Turn(float input)
{
	AddControllerYawInput(input);
}

void APlayerCharacter::LookUp(float input)
{
	AddControllerPitchInput(input);
}

void APlayerCharacter::SetWeaponRotation()
{
	FVector start;
	FRotator cameraRotation;
	FVector end;

	FHitResult result;
	FCollisionQueryParams param(NAME_None, true, this);
	GetController()->GetPlayerViewPoint(start, cameraRotation);

	end = start + (cameraRotation.Vector() * 100000.0);

	if (GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, param))
	{
		r = UKismetMathLibrary::FindLookAtRotation(start, result.Location);
	}
	else
	{
		r = UKismetMathLibrary::FindLookAtRotation(start, end);
	}

	FRotator wr = FRotator::ZeroRotator;
	wr.Yaw = r.Yaw - 90.f;
	wr.Roll = -r.Pitch;

	weaponActor->SetWorldRotation(wr);
	//weaponActor->SetRelativeRotation(wr);
}

void APlayerCharacter::StartFire()
{
	if (bSwapElement || bSwapWeapon)
	{
		return;
	}

	OnFireDelegate.ExecuteIfBound();
	if (!bFire)
	{
		bFire = true;
		GetWorldTimerManager().SetTimer(fireTh, this, &APlayerCharacter::StartFire, .2f, true);
	}
}

void APlayerCharacter::StopFire()
{
	bFire = false;
	GetWorldTimerManager().ClearTimer(fireTh);
}

void APlayerCharacter::StartSwapWeapon()
{
	bSwapWeapon = true;
}

void APlayerCharacter::StopSwapWeapon()
{
	//짧게 누를때
	if (bSwapWeapon)
	{
		bSwapWeapon = false;
		OnSwapWeaponDelegate.ExecuteIfBound();
	}
	else //if (!bSwapWeapon && GetWorldSettings()->TimeDilation < 1.f)//길게 누를때
	{
		OnToggleWeaponOverlayDelegate.ExecuteIfBound();
	}
	weaponHoldingtime = .0f;
	GetWorldSettings()->SetTimeDilation(1.f);
}

void APlayerCharacter::StartSwapElement()
{
	bSwapElement = true;
}

void APlayerCharacter::StopSwapElement()
{
	//짧게 누를때
	if (bSwapElement)
	{
		bSwapElement = false;
		OnSwapElementDelegate.ExecuteIfBound();
	}
	else //if(!bSwapElement && GetWorldSettings()->TimeDilation < 1.f) //길게 누를때
	{
		OnToggleElementOverlayDelegate.ExecuteIfBound();
	}
	elementHoldingtime = .0f;
	GetWorldSettings()->SetTimeDilation(1.f);
}

void APlayerCharacter::CheckHoldingKey()
{
	//무기 홀딩
	if (bSwapWeapon && !bSwapElement)
	{
		weaponHoldingtime = GetController<APlayerController>()->GetInputKeyTimeDown(FKey("Q"));
	}
	
	if (weaponHoldingtime >= .5f && bSwapWeapon)
	{
		GetWorldSettings()->SetTimeDilation(.1f);
		bSwapWeapon = false;
		OnToggleWeaponOverlayDelegate.ExecuteIfBound();
	}

	//원소 홀딩
	if (bSwapElement && !bSwapWeapon)
	{
		elementHoldingtime = GetController<APlayerController>()->GetInputKeyTimeDown(FKey("E"));
	}

	if (elementHoldingtime >= .5f && bSwapElement)
	{
		GetWorldSettings()->SetTimeDilation(.1f);
		bSwapElement = false;
		OnToggleElementOverlayDelegate.ExecuteIfBound();
	}
}

void APlayerCharacter::StartJump()
{
	if (jumpCount <= 0)
	{
		return;
	}
	FVector jumpDir = FVector::ZeroVector;
	jumpDir.Z = FindComponentByClass<UCharacterMovementComponent>()->JumpZVelocity;
	LaunchCharacter(jumpDir, false, true);
}

void APlayerCharacter::StopJump()
{
	if (jumpCount <= 0)
	{
		return;
	}
	else
	{
		jumpCount--;
	}
}
