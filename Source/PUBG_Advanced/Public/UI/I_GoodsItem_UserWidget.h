// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "I_GoodsItem_UserWidget.generated.h"


class AItemBase;
/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_GoodsItem_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
		void SetContentx(AItemBase* ItemBase,UTexture2D* Icon,FName Name,int32 Amount);

	
	UFUNCTION(BlueprintImplementableEvent)
		void SetContents(AItemBase* ItemBase, UTexture2D* Icon, FName Name, int32 Amount);



};
