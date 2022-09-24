// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PickUpHealth.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpHealth : public APickUpBase
{
	GENERATED_BODY()

public:

	APickUpHealth();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		int32 SingleWeight;

	virtual int32 GetWeight() override;


protected:


	virtual void BeginPlay() override;

	FString ItemHealthTablePath;

	UDataTable* ItemHealthTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	



};
