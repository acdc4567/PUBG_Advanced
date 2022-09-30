// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "Inventory_UserWidget.generated.h"

class APUBGA_PlayerController;
class AItemBase;
class APUBGA_PlayerState;

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UInventory_UserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	

	UFUNCTION()
		void ItemsInRangeChange_Handle(bool bIsOnHand);

	UFUNCTION()
		void UpdateList(bool bIsOnHand);

	UFUNCTION()
		void UpdateBackpackList(AItemBase* Item, bool bIsAdd);




public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	bool InitializePlayerController(APUBGA_PlayerController* APC);

	bool InitializePlayerState(APUBGA_PlayerState* APS);

	UFUNCTION(BlueprintImplementableEvent)
		void ClearChildrens();

	UFUNCTION(BlueprintImplementableEvent)
		void ClearChildrenxs();


	UFUNCTION(BlueprintImplementableEvent)
		void AddChildrens(AItemBase* ItemBase, UTexture2D* Icon, FName Name, int32 Amount);

	UFUNCTION(BlueprintImplementableEvent)
		void AddChildrenxs(AItemBase* ItemBase, UTexture2D* Icon, FName Name, int32 Amount);


};
