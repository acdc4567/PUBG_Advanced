// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"

#include "I_Equipment_UWidget.generated.h"

class UImage;
class APUBGA_PlayerController;
class APUBGA_PlayerState;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_Equipment_UWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		EInventoryLocationx Location = EInventoryLocationx::EIL_None;

	UPROPERTY(meta = (BindWidget))
		UImage* BgNone;

	UPROPERTY(meta = (BindWidget))
		UImage* Bg;

	UPROPERTY(meta = (BindWidget))
		UImage* Icon;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;


	UFUNCTION()
		void UpdateEquipment(AItemBase* Equipment, bool bIsAdd);

	UFUNCTION()
		void UpdateFashions(AItemBase* Fashion, bool bIsAdd);

	void UpdateShow();

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;






};
