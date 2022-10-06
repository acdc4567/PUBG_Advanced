// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "PUBGA_Enums.h"

#include "I_DragDropOperation.generated.h"

class AItemBase;

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (ExposeOnSpawn = "true"))
		AItemBase* DraggedItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (ExposeOnSpawn = "true"))
		EInventoryLocationx Locationx;
};
