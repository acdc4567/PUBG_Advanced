// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "ItemUseBase.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API AItemUseBase : public AItemBase
{
	GENERATED_BODY()
public:

	AItemUseBase();

protected:

	
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		float UseTime;






};
