// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Equipment_UWidget.h"
#include "Components/Image.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemBase.h"
#include "Items/ItemFashion.h"
#include "Items/ItemEquipment.h"
#include "UI/I_DragDropOperation.h"
#include "Items/PickUpBase.h"


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

void UI_Equipment_UWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	
	Bg->SetColorAndOpacity(FLinearColor(.01f, .01f, .01f, .6f));
}

void UI_Equipment_UWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseLeave(InMouseEvent);

	Bg->SetColorAndOpacity(FLinearColor(0.f, 0.f, 0.f, .6f));


}


bool UI_Equipment_UWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	bool bSuper=Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!PlayerControllerRef)return 0;
	UI_DragDropOperation* DragDropOp = Cast<UI_DragDropOperation>(InOperation);

	if (DragDropOp) {
		APickUpBase* DraggedItemCastToPUB = nullptr;

		switch (DragDropOp->Locationx) {
		case EInventoryLocationx::EIL_None:


			break;
		case EInventoryLocationx::EIL_Helmet:
			break;
		case EInventoryLocationx::EIL_Vest:
			break;
		case EInventoryLocationx::EIL_Backpack:
			break;
		case EInventoryLocationx::EIL_ClothesTop:
			break;
		case EInventoryLocationx::EIL_ClothesBottom:
			break;
		case EInventoryLocationx::EIL_Shoes:
			break;
		case EInventoryLocationx::EIL_VicinityList:
			switch (DragDropOp->DraggedItem->ItemType) {
			case EItemType::EIT_Weapon:
				break;
			case EItemType::EIT_Accessories:
				break;
			case EItemType::EIT_Ammo:
				break;
			case EItemType::EIT_Health:
				break;
			case EItemType::EIT_Boost:
				break;
			case EItemType::EIT_Helmet:
				if (PlayerControllerRef->PickupEquipment(DragDropOp->DraggedItem)) {
					DragDropOp->DraggedItem->Destroy();
					return 1||bSuper;
				}

				break;
			case EItemType::EIT_Vest:
				if (PlayerControllerRef->PickupEquipment(DragDropOp->DraggedItem)) {
					DragDropOp->DraggedItem->Destroy();
					return 1 || bSuper;
				}

				break;
			case EItemType::EIT_Backpack:
				if (PlayerControllerRef->PickupEquipment(DragDropOp->DraggedItem)) {
					DragDropOp->DraggedItem->Destroy();
					return 1 || bSuper;
				}

				break;
			case EItemType::EIT_Fashion:

				DraggedItemCastToPUB = Cast<APickUpBase>(DragDropOp->DraggedItem);
				if (DraggedItemCastToPUB) {
					UE_LOG(LogTemp, Warning, TEXT("GG"));
					PlayerControllerRef->PickupFashion(DraggedItemCastToPUB);
					DragDropOp->DraggedItem->Destroy();
					return 1 || bSuper;
				}
				
				break;
			case EItemType::EIT_MAX:
				break;
			default:
				break;
			}





			break;
		case EInventoryLocationx::EIL_BackpackList:
			break;
		case EInventoryLocationx::EIL_Weapon:
			break;
		case EInventoryLocationx::EIL_WeaponAcc:
			break;
		case EInventoryLocationx::EIL_MAX:
			break;
		default:
			break;
		}



	}
	return bSuper;
}










