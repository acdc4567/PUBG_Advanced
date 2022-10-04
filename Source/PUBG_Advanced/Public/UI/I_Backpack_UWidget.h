// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "I_Backpack_UWidget.generated.h"


class APUBGA_PlayerController;
class AItemBase;
class UI_GoodsItem_UserWidget;
class UScrollBox;
class APUBGA_PlayerState;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_Backpack_UWidget : public UUserWidget
{
	GENERATED_BODY()
protected:


	UFUNCTION()
		void UpdateList(AItemBase* Item, bool bIsAdd);

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UserInterfaces)
		TSubclassOf<UI_GoodsItem_UserWidget> GoodsItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
		UScrollBox* GoodsItemList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;




};
