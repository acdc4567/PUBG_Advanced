// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemEquipment : public AItemBase
{
	GENERATED_BODY()

public:
	AItemEquipment();

	FSTR_ItemEquipment* Datas = nullptr;

protected:

	FString ItemEquipmentTablePath;

	UDataTable* ItemEquipmentTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	

	FSTR_ItemEquipment Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemEquipment GetDatas() const { return Datas1; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* StaticMeshx2;




	
};
