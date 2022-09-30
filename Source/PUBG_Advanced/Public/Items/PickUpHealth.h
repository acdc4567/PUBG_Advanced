// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
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

	FSTR_ItemHealth* Datas = nullptr;
	FSTR_ItemHealth Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemHealth GetDatas() const { return Datas1; }


protected:


	virtual void BeginPlay() override;

	FString ItemHealthTablePath;

	UDataTable* ItemHealthTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	



};
