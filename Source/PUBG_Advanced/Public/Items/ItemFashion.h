// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemFashion.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemFashion : public AItemBase
{
	GENERATED_BODY()

public:
	AItemFashion();




protected:
	FString ItemFashionTablePath;

	UDataTable* ItemFashionTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	FSTR_ItemFashion* Datas = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		EFashionType FashionType;



	
};
