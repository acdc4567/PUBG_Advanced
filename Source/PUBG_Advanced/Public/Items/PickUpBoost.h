// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
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

protected:


	
	FString ItemBoostTablePath;

	UDataTable* ItemBoostTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual int32 GetWeight() override;




};
