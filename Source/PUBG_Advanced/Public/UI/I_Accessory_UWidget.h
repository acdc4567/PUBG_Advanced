// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"

#include "I_Accessory_UWidget.generated.h"

class UImage;
class APUBGA_PlayerController;
class APUBGA_PlayerState;
class AItemWeapon;
class AItemWeaponAcc;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UI_Accessory_UWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	FORCEINLINE void SetOwner(AItemWeapon* AccOwner) { Owner = AccOwner; }

	UFUNCTION()
		void UpdateWeaponAccDisplay(AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		EWeaponAccType AccTypex = EWeaponAccType::EWAT_MAX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		AItemWeapon* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		AItemWeaponAcc* Acc;

	
	UPROPERTY(meta = (BindWidget))
		UImage* Bg;

	UPROPERTY(meta = (BindWidget))
		UImage* Icon;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;





};
