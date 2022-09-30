// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
#include "PickUpBoost.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpBoost : public APickUpBase
{
	GENERATED_BODY()


public:

	APickUpBoost();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		int32 SingleWeight;

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
