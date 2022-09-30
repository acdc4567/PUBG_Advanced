// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
#include "PickUpFashion.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpFashion : public APickUpBase
{
	GENERATED_BODY()
public:

	APickUpFashion();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		EFashionType FashionType;

	FSTR_ItemFashion* Datas = nullptr;

	FSTR_ItemFashion Datas1;

	UFUNCTION(BlueprintPure)
		FORCEINLINE FSTR_ItemFashion GetDatas() const { return Datas1; }



protected:

	virtual void BeginPlay() override;


	FString ItemFashionTablePath;

	UDataTable* ItemFashionTableObject;

	virtual void OnConstruction(const FTransform& Transform) override;

	
};
