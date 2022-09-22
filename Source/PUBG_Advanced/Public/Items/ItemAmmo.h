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







protected:



	FString ItemAmmoTablePath;

	UDataTable* ItemAmmoTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	FSTR_ItemAmmo* Datas = nullptr;

	virtual int32 GetWeight() override;




};
