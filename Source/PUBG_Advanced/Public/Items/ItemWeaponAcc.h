// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemWeaponAcc.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemWeaponAcc : public AItemBase
{
	GENERATED_BODY()
	
public:

	AItemWeaponAcc();

	FSTR_ItemWeaponAcc* Datas = nullptr;

	FSTR_ItemWeaponAcc Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemWeaponAcc GetDatas() const { return Datas1; }

	virtual int32 GetWeight() override;

	EWeaponAccType AccType;

protected:

	

	

	FString ItemWeaponAccTablePath;

	UDataTable* ItemWeaponAccTableObject;



	virtual void OnConstruction(const FTransform& Transform) override;

	







};
