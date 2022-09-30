// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
#include "PickUpAmmo.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpAmmo : public APickUpBase
{
	GENERATED_BODY()
	

public:

	APickUpAmmo();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		int32 SingleWeight;

	virtual int32 GetWeight() override;

	FSTR_ItemAmmo* Datas = nullptr;

	FSTR_ItemAmmo Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemAmmo GetDatas() const { return Datas1; }

protected:

	FString ItemAmmoTablePath;

	UDataTable* ItemAmmoTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	





};
