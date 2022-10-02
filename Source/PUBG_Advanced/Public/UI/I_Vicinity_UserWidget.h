// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "I_Vicinity_UserWidget.generated.h"

class APUBGA_PlayerController;
class AItemBase;
class UI_GoodsItem_UserWidget;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_Vicinity_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:


	UFUNCTION()
		void UpdateList(bool bIsOnHand);

	UFUNCTION(BlueprintImplementableEvent)
		void SetContent(AItemBase* ItemBase, UTexture2D* Icon, FName Name, int32 Amount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UserInterfaces)
		TSubclassOf<UI_GoodsItem_UserWidget> GoodsItemWidgetClass;

	

	UFUNCTION(BlueprintImplementableEvent)
		void ClearChildrens();


	UFUNCTION(BlueprintImplementableEvent)
		void AddChildrens(AItemBase* ItemBase, UTexture2D* Icon, FName Name, int32 Amount);


	virtual void NativePreConstruct() override;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* GoodsItemList;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	bool InitializePlayerController(APUBGA_PlayerController* APC);

};
