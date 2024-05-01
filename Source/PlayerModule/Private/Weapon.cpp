// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerCharacter.h"
#include "WeaponDataAsset.h"
#include "WeaponDataTable.h"
#include "Bullet.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	weaponType = EWeaponTypeEnum::WT_Rifle;
	ammoElementType = EElementTypeEnum::ET_Normal;
	//owner = GetOwner<APlayerCharacter>();
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	pc = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (pc)
	{
		pc->OnFireDelegate.BindUObject(this, &AWeapon::Fire);
		pc->OnSwapWeaponDelegate.BindUObject(this, &AWeapon::SwapWeapon);
		pc->OnSwapElementDelegate.BindUObject(this, &AWeapon::SwapElement);
		pc->OnChangeWeaponTypeDelegate.BindUObject(this, &AWeapon::ChangeWeapon);
		pc->OnChangeElementTypeDelegate.BindUObject(this, &AWeapon::ChangeElement);
	}

	if (PlayerWeaponDataTable)
	{
		FPlayerWeaponStruct* weaponData;
		weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("RF"), FString(""));
		damage = weaponData->damage;
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWeapon::Fire()
{
	FVector start;
	FRotator cameraRotation;
	FVector end;
	FVector muzzleLoc;
	FRotator rot;

	FHitResult result;
	FCollisionQueryParams cParam(NAME_None, true, this);
	pc->GetController()->GetPlayerViewPoint(start, cameraRotation);
	muzzleLoc = weaponMesh->GetSocketLocation(FName("MuzzleFlash"));

	end = start + (cameraRotation.Vector() * 100000.0);
	if (GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, cParam))
	{
		rot = UKismetMathLibrary::FindLookAtRotation(muzzleLoc, result.Location);
		
	}
	else
	{
		rot = UKismetMathLibrary::FindLookAtRotation(muzzleLoc, end);
	}

	if (PlayerWeaponDataAsset)
	{
		switch (weaponType)
		{
		case EWeaponTypeEnum::WT_Rifle:
			if (PlayerWeaponDataAsset->RfBullet)
			{
				ABullet* bullet = GetWorld()->SpawnActor<ABullet>(PlayerWeaponDataAsset->RfBullet, muzzleLoc, rot);
				bullet->weapon = this;
				bullet->bulletDamage = damage;
				bullet->bulletType = ammoElementType;
			}
			break;
		case EWeaponTypeEnum::WT_GrenadeLauncher:
			if (PlayerWeaponDataAsset->RfBullet)
			{
				//rot.Pitch += 10.f;
				muzzleLoc = muzzleLoc + rot.Vector() * 20.f;
				ABullet* bullet = GetWorld()->SpawnActor<ABullet>(PlayerWeaponDataAsset->GLBullet, muzzleLoc, rot);
				bullet->weapon = this;
				bullet->bulletDamage = damage;
				bullet->bulletType = ammoElementType;
			}
			break;
		case EWeaponTypeEnum::WT_Shotgun:
			if (PlayerWeaponDataAsset->RfBullet)
			{
				for (int i = 0; i < 5; i++)
				{
					FRotator ranrot = rot;
					ranrot.Pitch += UKismetMathLibrary::RandomFloatInRange(-5.f, 5.f);
					ranrot.Yaw += UKismetMathLibrary::RandomFloatInRange(-5.f, 5.f);
					ABullet* bullet = GetWorld()->SpawnActor<ABullet>(PlayerWeaponDataAsset->SGBullet, muzzleLoc, ranrot);
					bullet->weapon = this;
					bullet->bulletDamage = damage;
					bullet->bulletType = ammoElementType;
				}
			}
			break;
		default:
			break;
		}
	}
}

void AWeapon::SwapWeapon()
{
	if (PlayerWeaponDataAsset && PlayerWeaponDataTable)
	{
		FPlayerWeaponStruct* weaponData;
		switch (weaponType)
		{
		case EWeaponTypeEnum::WT_Rifle:
			weaponType = EWeaponTypeEnum::WT_GrenadeLauncher;
			//weaponMesh->SkeletalMesh = PlayerWeaponDataAsset->GLMesh;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->GLMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("GL"), FString(""));
			damage = weaponData->damage;
			break;
		case EWeaponTypeEnum::WT_GrenadeLauncher:
			weaponType = EWeaponTypeEnum::WT_Shotgun;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->SGMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("SG"), FString(""));
			damage = weaponData->damage;
			break;
		case EWeaponTypeEnum::WT_Shotgun:
			weaponType = EWeaponTypeEnum::WT_Rifle;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->RFMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("RF"), FString(""));
			damage = weaponData->damage;
			break;
		default:
			weaponType = EWeaponTypeEnum::WT_Rifle;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->RFMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("RF"), FString(""));
			damage = weaponData->damage;
			break;
		}
	}
}

void AWeapon::ChangeWeapon(EWeaponTypeEnum p_WeaponType)
{
	if (PlayerWeaponDataAsset && PlayerWeaponDataTable)
	{
		FPlayerWeaponStruct* weaponData;

		switch (p_WeaponType)
		{
		case EWeaponTypeEnum::WT_Rifle:
			weaponType = p_WeaponType;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->RFMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("RF"), FString(""));
			damage = weaponData->damage;
			break;
		case EWeaponTypeEnum::WT_GrenadeLauncher:
			weaponType = p_WeaponType;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->GLMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("GL"), FString(""));
			damage = weaponData->damage;
			break;
		case EWeaponTypeEnum::WT_Shotgun:
			weaponType = p_WeaponType;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->SGMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("SG"), FString(""));
			damage = weaponData->damage;
			break;
		default:
			weaponType = EWeaponTypeEnum::WT_Rifle;
			weaponMesh->SetSkeletalMesh(PlayerWeaponDataAsset->RFMesh);

			weaponData = PlayerWeaponDataTable->FindRow<FPlayerWeaponStruct>(FName("RF"), FString(""));
			damage = weaponData->damage;
			break;
		}
	}
}

void AWeapon::SwapElement()
{
	switch (ammoElementType)
	{
	case EElementTypeEnum::ET_Normal:
		ammoElementType = EElementTypeEnum::ET_Venom;
		break;
	case EElementTypeEnum::ET_Venom:
		ammoElementType = EElementTypeEnum::ET_Freeze;
		break;
	case EElementTypeEnum::ET_Freeze:
		ammoElementType = EElementTypeEnum::ET_TongTong;
		break;
	case EElementTypeEnum::ET_TongTong:
		ammoElementType = EElementTypeEnum::ET_Normal;
		break;
	default:
		break;
	}
}

void AWeapon::ChangeElement(EElementTypeEnum p_ElementType)
{
	switch (p_ElementType)
	{
	case EElementTypeEnum::ET_Normal:
		ammoElementType = EElementTypeEnum::ET_Normal;
		break;
	case EElementTypeEnum::ET_Venom:
		ammoElementType = EElementTypeEnum::ET_Venom;
		break;
	case EElementTypeEnum::ET_Freeze:
		ammoElementType = EElementTypeEnum::ET_Freeze;
		break;
	case EElementTypeEnum::ET_TongTong:
		ammoElementType = EElementTypeEnum::ET_TongTong;
		break;
	default:
		break;
	}
}

