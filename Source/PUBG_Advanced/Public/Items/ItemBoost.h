// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemUseBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemBoost.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemBoost : public AItemUseBase
{
	GENERATED_BODY()


public:
	AItemBoost();

	virtual int32 GetWeight() override;
	
	FSTR_ItemBoost* Datas = nullptr;

	FSTR_ItemBoost Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemBoost GetDatas() const { return Datas1; }



protected:
	FString ItemBoostTablePath;

	UDataTable* ItemBoostTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	

	

	
};
