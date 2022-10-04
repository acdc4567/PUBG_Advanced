// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"

#include "I_Weapon_UWidget.generated.h"

class UImage;
class APUBGA_PlayerController;
class APUBGA_PlayerState;
class AItemWeapon;
class UTextBlock;
class UHorizontalBox;
class UCanvasPanel;
class UI_Accessory_UWidget;



/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_Weapon_UWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		int32 Locationx = 1;

protected:



	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		AItemWeapon* ItemWeapon=nullptr;



	UFUNCTION()
		void UpdateWeaponDisplay(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand);

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LocationID;
	
	UPROPERTY(meta = (BindWidget))
		UHorizontalBox* TopBox;

	UPROPERTY(meta = (BindWidget))
		UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* BulletTypeText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ClipAmountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* RemainingAmountText;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* AccCanvasPanel;

	UPROPERTY(meta = (BindWidget))
		UI_Accessory_UWidget* AccSight;

	UPROPERTY(meta = (BindWidget))
		UI_Accessory_UWidget* Acc_Muzzle;

	UPROPERTY(meta = (BindWidget))
		UI_Accessory_UWidget* Acc_Mag;

	UPROPERTY(meta = (BindWidget))
		UI_Accessory_UWidget* Acc_Foregrip;

	UPROPERTY(meta = (BindWidget))
		UI_Accessory_UWidget* Acc_Buttstock;


	FString ItemAmmoTablePath;

	UDataTable* ItemAmmoTableObject;

};
