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


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Mag;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Sight;

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










};
