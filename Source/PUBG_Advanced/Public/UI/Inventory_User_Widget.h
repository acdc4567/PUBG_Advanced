// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory_User_Widget.generated.h"

class APUBGA_PlayerController;
class APUBGA_PlayerState;
class UProgressBar;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UInventory_User_Widget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	bool InitializePlayerController(APUBGA_PlayerController* APC);

	bool InitializePlayerState(APUBGA_PlayerState* APS);

	UPROPERTY(meta = (BindWidget))
		UProgressBar* BackpackCapacityBar;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
		void UpdateList(AItemBase* Item, bool bIsAdd);


};
