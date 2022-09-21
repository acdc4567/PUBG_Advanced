// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
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

protected:


	virtual void BeginPlay() override;

	FString ItemEquipmentTablePath;

	UDataTable* ItemEquipmentTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	







};
