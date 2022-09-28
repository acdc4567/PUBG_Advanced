// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemWeapon.generated.h"

class AItemWeaponAcc;
class UAudioComponent;
class UParticleSystemComponent;
class APUBGA_Character;
class APUBGA_PlayerState;
class APUBGA_PlayerController;
class ABulletProjectile;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemWeapon : public AItemBase
{
	GENERATED_BODY()


public:
	AItemWeapon();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		int32 Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		EWeaponPosition Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		bool bIsOnHand;

	FSTR_ItemWeapon* Datas = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		AItemWeaponAcc* AccMagObj;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		AItemWeaponAcc* AccMuzzleObj;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		AItemWeaponAcc* AccSightObj;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		AItemWeaponAcc* AccForegripObj;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		AItemWeaponAcc* AccButtstockObj;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Sight;


protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Mag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Foregrip;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* ButtStock;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UAudioComponent* AudioC;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UParticleSystemComponent* FireFlash;


	FString ItemWeaponTablePath;

	UDataTable* ItemWeaponTableObject;

	FString ItemWeaponAccTablePath;

	UDataTable* ItemWeaponAccTableObject;


	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyCharacter)
		APUBGA_Character* MyCharacterRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		APUBGA_PlayerState* PlayerStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		APUBGA_PlayerController* PlayerControllerRef;

	int32 CheckAmmoAmount();

	void CalculateOffsetPer(float & Vertical,float & Horizontal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TSubclassOf<ABulletProjectile> ProjectileClass;

	FTransform GetBulletInitTransform();









public:

	UFUNCTION(BlueprintCallable)
	void UpdateMag(AItemWeaponAcc* MagAccActor);

	UFUNCTION(BlueprintCallable)
		void UpdateMuzzle(AItemWeaponAcc* MuzzleAccActor);

	UFUNCTION(BlueprintCallable)
		void UpdateSight(AItemWeaponAcc* SightAccActor);

	UFUNCTION(BlueprintCallable)
		void UpdateForegrip(AItemWeaponAcc* ForegripAccActor);

	UFUNCTION(BlueprintCallable)
		void UpdateButtstock(AItemWeaponAcc* ButtstockAccActor);

	UFUNCTION(BlueprintCallable)
		void PlayFiringSound();

	UFUNCTION(BlueprintCallable)
		void PlayFiringFlash();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GunMech)
		EShootMode ShootMode=EShootMode::ESM_Auto;

	void SwitchShootMode();

	void PressFire();

	void ReleaseFire();

	FGate FireGate;

	FTimerHandle TH_FireTimer;

	void AutoFire();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FireFlashes)
		bool bCanPlayFiringFlash = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		float FireTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		int32 ClipSize = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		int32 Need = 0;

	void ReloadClip();

	void FilledClip();

	void ChangeBullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		bool bSightOpen = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		bool bNeedReloadBullet = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		float ReadyYaw = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		float ReadyPitch = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MyPlayerState)
		float FireInterval = 0.f;










};
