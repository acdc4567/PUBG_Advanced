// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemWeapon.h"
#include "Items/ItemWeaponAcc.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PUBGA_Character.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Bullets/BulletProjectile.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"



AItemWeapon::AItemWeapon() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(Scene);

	Mag = CreateDefaultSubobject<UStaticMeshComponent>("Mag");
	Mag->SetCollisionProfileName("NoCollision");
	Mag->SetupAttachment(SkeletalMesh);

	Muzzle = CreateDefaultSubobject<UStaticMeshComponent>("Muzzle");
	Muzzle->SetCollisionProfileName("NoCollision");
	Muzzle->SetupAttachment(SkeletalMesh);

	Sight = CreateDefaultSubobject<UStaticMeshComponent>("Sight");
	Sight->SetCollisionProfileName("NoCollision");
	Sight->SetupAttachment(SkeletalMesh);

	Foregrip = CreateDefaultSubobject<UStaticMeshComponent>("Foregrip");
	Foregrip->SetCollisionProfileName("NoCollision");
	Foregrip->SetupAttachment(SkeletalMesh);

	ButtStock = CreateDefaultSubobject<UStaticMeshComponent>("ButtStock");
	ButtStock->SetCollisionProfileName("NoCollision");
	ButtStock->SetupAttachment(SkeletalMesh);

	AudioC = CreateDefaultSubobject<UAudioComponent>("Audio");
	AudioC->SetupAttachment(SkeletalMesh);

	FireFlash = CreateDefaultSubobject<UParticleSystemComponent>("FireFlash");
	FireFlash->bAutoActivate = 0;
	FireFlash->SetWorldScale3D(FVector(.3f));
	FireFlash->SetupAttachment(SkeletalMesh);

	ItemWeaponTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeapon.DT_ItemWeapon'");
	ItemWeaponTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponTablePath));

	ItemWeaponAccTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeaponAcc.DT_ItemWeaponAcc'");
	ItemWeaponAccTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponAccTablePath));

	

}

void AItemWeapon::OnConstruction(const FTransform& Transform) {

	FSTR_ItemWeapon* ItemWeaponRow = nullptr;
	ItemWeaponRow = ItemWeaponTableObject->FindRow<FSTR_ItemWeapon>(ID, TEXT(""));

	if (ItemWeaponRow) {
		Datas = ItemWeaponRow;
		Init(EItemType::EIT_Weapon,ItemWeaponRow->Name);

		SkeletalMesh->SetSkeletalMesh(ItemWeaponRow->SkeletalMesh);

		Mag->SetStaticMesh(ItemWeaponRow->DefaultMag);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
		Mag->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Mag")));
		Muzzle->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Muzzle")));

		if (ItemWeaponRow->DefaultSight) {
			Sight->SetStaticMesh(ItemWeaponRow->DefaultSight);
			Sight->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Sight_Default")));

		}
		if (ItemWeaponRow->bCanGrip) {
			Foregrip->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Foregrip")));
		}
		if (ItemWeaponRow->DefaultButtstock) {
			ButtStock->SetStaticMesh(ItemWeaponRow->DefaultButtstock);
			ButtStock->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Buttstock")));

		}
		if (ItemWeaponRow->FireFlashParticles) {
			FireFlash->SetTemplate(ItemWeaponRow->FireFlashParticles);
			FireFlash->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Muzzle")));
		}

	}
	


}

void AItemWeapon::BeginPlay() {
	Super::BeginPlay();

	MyCharacterRef = Cast<APUBGA_Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (MyCharacterRef) {
		
		PlayerStateRef= MyCharacterRef->GetPlayerStateRef();
		
		PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this,0));
		ProjectileClass = MyCharacterRef->ProjectileClass;
	}



}


void AItemWeapon::UpdateMag(AItemWeaponAcc* MagAccActor) {

	AccMagObj = MagAccActor;
	if (MagAccActor == nullptr) {
		Mag->SetStaticMesh(Datas->DefaultMag);

	}
	else {
		FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
		ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(AccMagObj->ID, TEXT(""));

		if (ItemWeaponAccRow) {
			if (ID != "2") {
				Mag->SetStaticMesh(ItemWeaponAccRow->StaticMesh);
			}
			else {
				Mag->SetStaticMesh(ItemWeaponAccRow->StaticMesh2);
			}

		}

	}

}

void AItemWeapon::UpdateMuzzle(AItemWeaponAcc* MuzzleAccActor) {

	AccMuzzleObj = MuzzleAccActor;

	if (MuzzleAccActor == nullptr) {
		Muzzle->SetStaticMesh(nullptr);
	}
	else {
		FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
		ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(AccMuzzleObj->ID, TEXT(""));
		if (ItemWeaponAccRow) {
			Muzzle->SetStaticMesh(ItemWeaponAccRow->StaticMesh);

		}
	}

}

void AItemWeapon::UpdateSight(AItemWeaponAcc* SightAccActor) {
	AccSightObj = SightAccActor;
	if (SightAccActor == nullptr) {
		Sight->SetStaticMesh(Datas->DefaultSight);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
		Sight->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Sight_Default")));

	
	}
	else {
		FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
		ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(AccSightObj->ID, TEXT(""));
		if (ItemWeaponAccRow) {
			Sight->SetStaticMesh(ItemWeaponAccRow->StaticMesh);
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
			Sight->AttachToComponent(SkeletalMesh, AttachmentRules, ItemWeaponAccRow->SocketName);

		}

	}

}

void AItemWeapon::UpdateForegrip(AItemWeaponAcc* ForegripAccActor) {
	AccForegripObj = ForegripAccActor;
	if (ForegripAccActor==nullptr) {
		Foregrip->SetStaticMesh(nullptr);
	}
	else {
		FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
		ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(AccForegripObj->ID, TEXT(""));
		if (ItemWeaponAccRow) {
			Foregrip->SetStaticMesh(ItemWeaponAccRow->StaticMesh);

		}

	}

}

void AItemWeapon::UpdateButtstock(AItemWeaponAcc* ButtstockAccActor) {
	AccButtstockObj = ButtstockAccActor;
	if (ButtstockAccActor == nullptr) {
		ButtStock->SetStaticMesh(Datas->DefaultButtstock);
	}
	else {

		FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
		ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(AccButtstockObj->ID, TEXT(""));
		if (ItemWeaponAccRow) {
			ButtStock->SetStaticMesh(ItemWeaponAccRow->StaticMesh);
		
		}

	}

}

void AItemWeapon::PlayFiringSound() {

	if (AccMuzzleObj) {
		if (AccMuzzleObj->Datas->bIsSuppressor) {
			AudioC->SetSound(Datas->FireSoundSuppressor);

		}
		else {
			AudioC->SetSound(Datas->FireSound);
		}
		
	}
	else {
		AudioC->SetSound(Datas->FireSound);
	}

	AudioC->Play();


}

void AItemWeapon::PlayFiringFlash() {

	if (AccMuzzleObj) {
		if (AccMuzzleObj->Datas->bIsNotFlash) {
			FireFlash->SetActive(1,1);
		}

	}
	FireFlash->SetActive(1, 1);

}


void AItemWeapon::SwitchShootMode() {

	if (Datas->bAutoMode) {
		if (ShootMode == EShootMode::ESM_Single) {
			ShootMode = EShootMode::ESM_Auto;
		}
		else {
			ShootMode = EShootMode::ESM_Single;
		}
	}




}



void AItemWeapon::PressFire() {
	FireGate.Open();
	AutoFire();
}



void AItemWeapon::AutoFire() {
	if (!MyCharacterRef || !PlayerControllerRef || !PlayerStateRef)return;
	
	if (FireGate.IsGateOpen()) {
		//GetWorldTimerManager().ClearTimer(TH_FireTimer);
		if (ShootMode == EShootMode::ESM_Auto) {
			GetWorldTimerManager().SetTimer(TH_FireTimer, this, &AItemWeapon::AutoFire, Datas->FiringInterval);
			if (Ammo>0) {
				PlayFiringSound();
				if (bCanPlayFiringFlash) {
					PlayFiringFlash();
				}
				Ammo -= 1;
				FireInterval = GetWorld()->GetTimeSeconds() - FireTime;
				FireTime = GetWorld()->GetTimeSeconds();
				if (Datas->ReplaceBulletTime>0.f) {
					bNeedReloadBullet = 1;
				}
				bool bTemp = !(MyCharacterRef->GetIsProne() && !MyCharacterRef->GetIsSightAiming());
				MyCharacterRef->SetIsAiming(bTemp);
				
				MyCharacterRef->UpdateWeaponDisplay(PlayerControllerRef->CalculateHoldGunSocket());
				if (MyCharacterRef->GetIsSightAiming()) {
					MyCharacterRef->GetFPS_Arms()->GetAnimInstance()->Montage_Play(MyCharacterRef->GetArmsFireMontage(),4.f);

				}
				else {
					MyCharacterRef->PlayMontage(EMontageType::EMT_Fire);
				}

				if (Datas->ReplaceBulletTime > 0.f) {
					MyCharacterRef->PlayCamShake(0);
				}
				else {
					MyCharacterRef->PlayCamShake(1);
				}
				int32 RandomInt32=0;
				if (FMath::RandBool()) {
					RandomInt32 = 1;
				}
				else {
					RandomInt32 = 0;
				}
				float fMultiplier = 0.f;

				if (FireInterval<.4f) {
					fMultiplier = 2.f;
				}
				else {
					fMultiplier = .1f;
				}
				float HPer, VPer;
				CalculateOffsetPer(HPer, VPer);

				ReadyYaw = RandomInt32 * Datas->HorizontalOffset * (1 - HPer);
				ReadyPitch = fMultiplier * Datas->VerticalOffset * (1 - VPer);
				MyCharacterRef->AdddedPerToZero();
				MyCharacterRef->AddRecoil(ReadyYaw, ReadyPitch, Datas->FiringInterval,FireInterval);
				
				FTransform SpawnTransform = GetBulletInitTransform();
				ABulletProjectile* Projectile = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ProjectileClass, SpawnTransform);
				if (Projectile) {
					Projectile->InitVelocity = Datas->InitVelocity;
					Projectile->f100MVelocity = Datas->f100MVelocity;
					Projectile->f300MVelocity = Datas->f300MVelocity;
					Projectile->f500MVelocity = Datas->f500MVelocity;


					Projectile->FinishSpawning(SpawnTransform);
				}


			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("No Bullets!!"));
			}
			


		}


	}



}

void AItemWeapon::ReleaseFire() {
	FireGate.Close();
	GetWorldTimerManager().ClearTimer(TH_FireTimer);
}

int32 AItemWeapon::CheckAmmoAmount() {
	if (!PlayerStateRef)return 0;
	int32 RemainAmount = PlayerStateRef->GetAmmoAmount(Datas->UseAmmoID);
	int32 NeedAmount = 0;
	
	if (RemainAmount > 0) {
		if (AccMagObj) {
			ClipSize = AccMagObj->Datas->ClipCapacity;
		}
		else {
			ClipSize = Datas->ClipSize;
		}
		Need = ClipSize - Ammo;
		if (Need > 0 ) {
			
			NeedAmount = FMath::Clamp(Need,1,RemainAmount);
			return NeedAmount;
		}
		else {
			return 0;
		}


	}
	else {
		return 0;
	}


	return 0;

}


void AItemWeapon::ReloadClip() {
	if (!MyCharacterRef)return;
	if (!PlayerControllerRef)return;
	if (CheckAmmoAmount() > 0) {
		PlayerControllerRef->SetRunPressed(0);
		float ReloadRate = 0.f;
		if (AccMagObj) {
			ReloadRate = AccMagObj->Datas->ClipRate * Datas->ReplaceClipTime;
			
		}
		else {
			ReloadRate = Datas->ReplaceClipTime;
			
		}
		if (MyCharacterRef->GetIsProne() && ReloadRate != 0.f) {
			ReloadRate = PlayerControllerRef->ReplaceClipTime_Prone / ReloadRate;
			
		}
		else {
			if (ReloadRate != 0.f) {
				ReloadRate = PlayerControllerRef->ReplaceClipTime_Stand / ReloadRate;
				
			}
		}
		
		MyCharacterRef->PlayMontage(EMontageType::EMT_Reload,ReloadRate);

		if (MyCharacterRef->GetIsAiming() || MyCharacterRef->GetIsSightAiming()) {
			PlayerControllerRef->ReverseHoldAiming();
		}



	}



}


void AItemWeapon::FilledClip() {

	int32 NeedAmount = CheckAmmoAmount();
	Ammo += NeedAmount;
	PlayerStateRef->UpdateAmmoAmount(Datas->UseAmmoID, 0, NeedAmount);
	
}

void AItemWeapon::ChangeBullet() {
	if (!PlayerControllerRef)return;
	if (!MyCharacterRef)return;
	if (Datas->ReplaceBulletTime > 0.f) {
		if (Ammo > 0) {
			bSightOpen = MyCharacterRef->GetIsSightAiming();
			PlayerControllerRef->ReverseHoldAiming();
			MyCharacterRef->PlayMontage(EMontageType::EMT_ReloadBullet);
		}
	}




}



void AItemWeapon::CalculateOffsetPer(float& Vertical, float& Horizontal) {
	float VerticalPer = 0.f;
	float HorizontalPer = 0.f;
	if (AccMuzzleObj) {
		VerticalPer = AccMuzzleObj->Datas->VerticalAdjPer;
		HorizontalPer = AccMuzzleObj->Datas->HorizontalAdjPer;
	}
	if (AccForegripObj) {
		VerticalPer += AccForegripObj->Datas->VerticalAdjPer;
		HorizontalPer += AccForegripObj->Datas->HorizontalAdjPer;
	}
	if (AccButtstockObj) {
		VerticalPer += AccButtstockObj->Datas->VerticalAdjPer;
		HorizontalPer += AccButtstockObj->Datas->HorizontalAdjPer;
	}
	Vertical = VerticalPer;
	Horizontal = HorizontalPer;



}

FTransform AItemWeapon::GetBulletInitTransform() {
	if(!MyCharacterRef)return FTransform();
	if (!PlayerControllerRef)return FTransform();

	float OffsetMin = 0.f;
	float OffsetMax = 0.f;
	int32 Multiplier = 0;


	if (!MyCharacterRef->GetIsSightAiming()) {
		if (PlayerControllerRef->GetIsHoldAiming()) {
			if (PlayerControllerRef->GetMoveForwardAxis() == 0.f && PlayerControllerRef->GetMoveRightAxis() == 0.f) {
				OffsetMin = Datas->CrossOffset_Min_AimStillness;
				OffsetMax = Datas->CrossOffset_Max_AimStillness;
			}
			else {
				OffsetMin = Datas->CrossOffset_Min_AimMove;
				OffsetMax = Datas->CrossOffset_Max_AimMove;
			}
		}
		else {
			if (PlayerControllerRef->GetMoveForwardAxis() == 0.f && PlayerControllerRef->GetMoveRightAxis() == 0.f) {
				OffsetMin = Datas->CrossOffset_Min_Stillness;
				OffsetMax = Datas->CrossOffset_Max_Stillness;
			}
			else {
				OffsetMin = Datas->CrossOffset_Min_Move;
				OffsetMax = Datas->CrossOffset_Max_Move;
			}
		}

		FTransform RetTransform;
		FVector SpawnVector = MyCharacterRef->GetFollowCamera()->GetForwardVector() * 300.f + MyCharacterRef->GetFollowCamera()->GetComponentLocation();
		float RightOffsetFloat = FMath::RandRange(OffsetMin, OffsetMax);
		FVector RightOffset = MyCharacterRef->GetFollowCamera()->GetRightVector() * RightOffsetFloat;
		SpawnVector += RightOffset;
		float UpOffsetFloat = FMath::RandRange(OffsetMin, OffsetMax);
		FVector UpOffset = MyCharacterRef->GetFollowCamera()->GetUpVector() * UpOffsetFloat;
		SpawnVector += UpOffset;
		RetTransform.SetLocation(SpawnVector);
		FRotator SpawnRotation = MyCharacterRef->GetControlRotation();
		FQuat SpawnQuat = SpawnRotation.Quaternion();
		RetTransform.SetRotation(SpawnQuat);
		RetTransform.SetScale3D(FVector(1.f));

		return RetTransform;



	}
	else {
		if (AccSightObj) {
			Multiplier = AccSightObj->Datas->SightMultiple;
		}
		else {
			Multiplier = 0;
		}

		
		FName SocksName;
		if (Multiplier==0) {
			SocksName = "Socket_BulletDefault";
		}
		else if (Multiplier == 1) {
			SocksName = "Socket_Bullet1x";
		}
		else if (Multiplier == 4) {
			SocksName = "Socket_Bullet4x";
		}
		const USkeletalMeshSocket* GunSocket = SkeletalMesh->GetSocketByName(SocksName);
		return GunSocket->GetSocketTransform(SkeletalMesh);


	}
	
	return FTransform();
}









