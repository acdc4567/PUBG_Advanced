// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "PickUpWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpWeapon : public APickUpBase
{
	GENERATED_BODY()

public:

	APickUpWeapon();



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		int32 Ammo;

	
	FSTR_ItemWeapon* Datas;

	UPROPERTY(VisibleAnywhere, Category = Publics)
		FSTR_ItemWeapon Datas1;

	UFUNCTION(BlueprintPure)
		FSTR_ItemWeapon GetDatas() const;


protected:

	FString ItemWeaponTablePath;

	UDataTable* ItemWeaponTableObject;


	virtual void OnConstruction(const FTransform& Transform) override;

	



	
};
