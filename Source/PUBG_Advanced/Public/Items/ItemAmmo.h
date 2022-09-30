// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemAmmo : public AItemBase
{
	GENERATED_BODY()

public:
	AItemAmmo();

	virtual int32 GetWeight() override;

	FSTR_ItemAmmo* Datas = nullptr;

	FSTR_ItemAmmo Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemAmmo GetDatas() const { return Datas1; }


protected:



	FString ItemAmmoTablePath;

	UDataTable* ItemAmmoTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	

	




};
