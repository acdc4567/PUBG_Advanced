// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemWeapon.generated.h"

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

	FString ItemWeaponTablePath;

	UDataTable* ItemWeaponTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	FSTR_ItemWeapon* Datas = nullptr;




	
};
