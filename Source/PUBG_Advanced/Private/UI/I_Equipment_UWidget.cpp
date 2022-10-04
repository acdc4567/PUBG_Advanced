// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Equipment_UWidget.h"
#include "Components/Image.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemBase.h"
#include "Items/ItemFashion.h"
#include "Items/ItemEquipment.h"


void UI_Equipment_UWidget::NativeConstruct() {
	Super::NativeConstruct();
	if (Location != EInventoryLocationx::EIL_None) {
		PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerControllerRef) {
			PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
			if (PlayerStateRef) {
				PlayerStateRef->OnEquipmentChanged.AddDynamic(this, &UI_Equipment_UWidget::UpdateEquipment);
				PlayerStateRef->OnFashionChanged.AddDynamic(this, &UI_Equipment_UWidget::UpdateFashions);
				UpdateShow();
			}

		}



	}
	else {
		Icon->SetVisibility(ESlateVisibility::Hidden);
		Bg->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UI_Equipment_UWidget::NativeDestruct() {
	Super::NativeDestruct();
	if (Location != EInventoryLocationx::EIL_None) {

		PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerControllerRef) {
			PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
			if (PlayerStateRef) {
				PlayerStateRef->OnEquipmentChanged.RemoveDynamic(this, &UI_Equipment_UWidget::UpdateEquipment);
				PlayerStateRef->OnFashionChanged.RemoveDynamic(this, &UI_Equipment_UWidget::UpdateFashions);


			}


		}
	}

	


}

void UI_Equipment_UWidget::UpdateEquipment(AItemBase* Equipment, bool bIsAdd) {
	if (Location == EInventoryLocationx::EIL_Helmet || Location == EInventoryLocationx::EIL_Vest || Location == EInventoryLocationx::EIL_Backpack) {
		UpdateShow();
	}


}

void UI_Equipment_UWidget::UpdateFashions(AItemBase* Fashion, bool bIsAdd) {
	if (Location == EInventoryLocationx::EIL_ClothesTop || Location == EInventoryLocationx::EIL_ClothesBottom || Location == EInventoryLocationx::EIL_Shoes) {
		UpdateShow();
	}


}

void UI_Equipment_UWidget::UpdateShow() {
	if (!PlayerStateRef)return;
	AItemBase* ItemBase = nullptr;
	UTexture2D* ItemIcon = nullptr;



	if (Location == EInventoryLocationx::EIL_Helmet || Location == EInventoryLocationx::EIL_Vest || Location == EInventoryLocationx::EIL_Backpack) {
		TArray<AItemBase*> Equipments = PlayerStateRef->GetEquipments();

		for (AItemBase* Equipment : Equipments) {

			if (Equipment->ItemType==EItemType::EIT_Helmet&&Location==EInventoryLocationx::EIL_Helmet) {
				ItemBase = Equipment;
				break;
			}
			if (Equipment->ItemType == EItemType::EIT_Vest && Location == EInventoryLocationx::EIL_Vest) {
				ItemBase = Equipment;
				break;
			}
			if (Equipment->ItemType == EItemType::EIT_Backpack && Location == EInventoryLocationx::EIL_Backpack) {
				ItemBase = Equipment;
				break;
			}

		}

	}
	else {
		TArray<AItemBase*> Fashions = PlayerStateRef->GetFashions();
		for (AItemBase* Fashion : Fashions) {
			AItemFashion* FashionIF = Cast<AItemFashion>(Fashion);
			if (FashionIF) {
				if ((FashionIF->FashionType == EFashionType::EFT_ClothTop|| FashionIF->FashionType == EFashionType::EFT_Whole) && Location == EInventoryLocationx::EIL_ClothesTop) {
					ItemBase = Fashion;
					break;
				}
				if (FashionIF->FashionType == EFashionType::EFT_ClothBottom && Location == EInventoryLocationx::EIL_ClothesBottom) {
					ItemBase = Fashion;
					break;
				}
				if (FashionIF->FashionType == EFashionType::EFT_Shoes && Location == EInventoryLocationx::EIL_Shoes) {
					ItemBase = Fashion;
					break;
				}
			}

			

		}


	}


	if (ItemBase) {

		AItemEquipment* IBCastToIE = Cast<AItemEquipment>(ItemBase);
		if (IBCastToIE) {
			ItemIcon = IBCastToIE->Datas->Icon;
		}
		else {
			AItemFashion* IBCastToIF = Cast<AItemFashion>(ItemBase);
			if (IBCastToIF) {
				ItemIcon = IBCastToIF->Datas->Icon;
			}

		}

		Bg->SetVisibility(ESlateVisibility::Visible);
		Icon->SetBrushFromTexture(ItemIcon);
		Icon->SetVisibility(ESlateVisibility::Visible);
		BgNone->SetVisibility(ESlateVisibility::Hidden);




	}
	else {
		Bg->SetVisibility(ESlateVisibility::Hidden);
		Icon->SetVisibility(ESlateVisibility::Hidden);
		BgNone->SetVisibility(ESlateVisibility::Visible);

	}







}
