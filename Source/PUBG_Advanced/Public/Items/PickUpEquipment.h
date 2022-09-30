// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
#include "PickUpEquipment.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpEquipment : public APickUpBase
{
	GENERATED_BODY()
	
public:

	APickUpEquipment();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		EItemType EquipmentType;

	FSTR_ItemEquipment* Datas = nullptr;


	FSTR_ItemEquipment Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemEquipment GetDatas() const { return Datas1; }


protected:


	virtual void BeginPlay() override;

	FString ItemEquipmentTablePath;

	UDataTable* ItemEquipmentTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	







};
