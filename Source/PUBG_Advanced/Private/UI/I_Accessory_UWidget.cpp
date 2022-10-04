// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Accessory_UWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemWeapon.h"
#include "Items/ItemWeaponAcc.h"
#include "Components/Image.h"




void UI_Accessory_UWidget::NativeConstruct() {
	Super::NativeConstruct();
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnWeaponAccChanged.AddDynamic(this, &UI_Accessory_UWidget::UpdateWeaponAccDisplay);
			UpdateWeaponAccDisplay(nullptr,0,nullptr,EWeaponAccType::EWAT_MAX);

		}

	}

}

void UI_Accessory_UWidget::NativeDestruct() {
	Super::NativeDestruct();
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnWeaponAccChanged.RemoveDynamic(this, &UI_Accessory_UWidget::UpdateWeaponAccDisplay);
		}


	}




}

void UI_Accessory_UWidget::UpdateWeaponAccDisplay(AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType) {
	if (!PlayerStateRef)return;
	if (!Owner)return;

	switch (AccTypex) {
	case EWeaponAccType::EWAT_Sight:
		Acc = Owner->AccSightObj;
		break;
	case EWeaponAccType::EWAT_Muzzle:
		Acc = Owner->AccMuzzleObj;
		break;
	case EWeaponAccType::EWAT_Foregrip:
		Acc = Owner->AccForegripObj;
		break;
	case EWeaponAccType::EWAT_Mag:
		Acc = Owner->AccMagObj;
		break;
	case EWeaponAccType::EWAT_Buttstock:
		Acc = Owner->AccButtstockObj;
		break;
	case EWeaponAccType::EWAT_MAX:
		break;
	default:
		break;
	}

	if (Acc) {
		Icon->SetVisibility(ESlateVisibility::Visible);
		Icon->SetBrushFromTexture(Acc->Datas->Icon);


	}
	else {
		Icon->SetVisibility(ESlateVisibility::Hidden);
	}



}

void UI_Accessory_UWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (Acc) {
		Bg->SetColorAndOpacity(FLinearColor(.498039f, .498039f, .498039f, .3f));
	}
	

}

void UI_Accessory_UWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseLeave(InMouseEvent);
	if (Acc) {
		Bg->SetColorAndOpacity(FLinearColor(.498039f, .498039f, .498039f, .15f));
	}
	
}
