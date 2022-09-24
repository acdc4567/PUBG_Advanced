// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemUseBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemHealth.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemHealth : public AItemUseBase
{
	GENERATED_BODY()


public:
	AItemHealth();

	virtual int32 GetWeight() override;
protected:
	FString ItemHealthTablePath;

	UDataTable* ItemHealthTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	FSTR_ItemHealth* Datas = nullptr;


	

	
};
