// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUpBase.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PickUpWeaponAcc.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpWeaponAcc : public APickUpBase
{
	GENERATED_BODY()
public:

	APickUpWeaponAcc();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		EWeaponAccType AccType;

	virtual int32 GetWeight() override;

protected:

	virtual void BeginPlay() override;



	FString ItemWeaponAccTablePath;

	UDataTable* ItemWeaponAccTableObject;


	virtual void OnConstruction(const FTransform& Transform) override;

	





};
