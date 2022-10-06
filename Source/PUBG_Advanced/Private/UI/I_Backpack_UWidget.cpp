// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Backpack_UWidget.h"
#include "UI/I_GoodsItem_UserWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Components/ScrollBox.h"
#include "Items/ItemWeaponAcc.h"
#include "Items/ItemAmmo.h"
#include "Items/ItemHealth.h"
#include "Items/ItemBoost.h"
#include "UI/I_DragDropOperation.h"
#include "Items/PickUpBase.h"


void UI_Backpack_UWidget::UpdateList(AItemBase* Item, bool bIsAdd) {
	if (!PlayerStateRef)return;
	if (!GoodsItemWidgetClass)return;



	GoodsItemList->ClearChildren();

	TArray<AItemBase*> ItemsInBackpack = PlayerStateRef->GetItems();
	int32 Amount = 0;
	FName Name;
	UTexture2D* Icon = nullptr;

	AItemWeaponAcc* BPItemCastToIWA = nullptr;
	AItemAmmo* BPItemCastToIA = nullptr;
	AItemHealth* BPItemCastToIH = nullptr;
	AItemBoost* BPItemCastToIBo = nullptr;


	UI_GoodsItem_UserWidget* GoodsWidget = nullptr;

	for (AItemBase* ItemInBackpack : ItemsInBackpack) {

		Amount = ItemInBackpack->Amount;


		switch (ItemInBackpack->ItemType) {
		case EItemType::EIT_Weapon:


			break;
		case EItemType::EIT_Accessories:
			BPItemCastToIWA = Cast<AItemWeaponAcc>(ItemInBackpack);
			if (BPItemCastToIWA) {
				Name = BPItemCastToIWA->Datas->Name;
				Icon= BPItemCastToIWA->Datas->Icon;
				Amount = 0;
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget) {
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount, EInventoryLocationx::EIL_BackpackList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}


			break;
		case EItemType::EIT_Ammo:
			BPItemCastToIA = Cast<AItemAmmo>(ItemInBackpack);
			if (BPItemCastToIA) {
				Name = BPItemCastToIA->Datas->Name;
				Icon = BPItemCastToIA->Datas->Icon;
				
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget) {
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount, EInventoryLocationx::EIL_BackpackList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Health:
			BPItemCastToIH = Cast<AItemHealth>(ItemInBackpack);
			if (BPItemCastToIH) {
				Name = BPItemCastToIH->Datas->Name;
				Icon = BPItemCastToIH->Datas->Icon;

				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget) {
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount, EInventoryLocationx::EIL_BackpackList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Boost:
			BPItemCastToIBo = Cast<AItemBoost>(ItemInBackpack);
			if (BPItemCastToIBo) {
				Name = BPItemCastToIBo->Datas->Name;
				Icon = BPItemCastToIBo->Datas->Icon;

				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget) {
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount, EInventoryLocationx::EIL_BackpackList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Helmet:


			break;
		case EItemType::EIT_Vest:


			break;
		case EItemType::EIT_Backpack:


			break;
		case EItemType::EIT_Fashion:


			break;
		case EItemType::EIT_MAX:
			break;
		default:
			break;
		}




	}






}

void UI_Backpack_UWidget::NativeConstruct() {
	Super::NativeConstruct();


	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnItemsChanged.AddDynamic(this,&UI_Backpack_UWidget::UpdateList);
			UpdateList(nullptr,0);

		}

	}


}

void UI_Backpack_UWidget::NativeDestruct() {

	Super::NativeDestruct();
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnItemsChanged.RemoveDynamic(this, &UI_Backpack_UWidget::UpdateList);
		}
		

	}

}

bool UI_Backpack_UWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	bool bSuper = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
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
				DraggedItemCastToPUB = Cast<APickUpBase>(DragDropOp->DraggedItem);
				if (DraggedItemCastToPUB) {
					if (PlayerControllerRef->PickupGoods(DraggedItemCastToPUB)) {
						DragDropOp->DraggedItem->Destroy();
						return 1 || bSuper;
					}

				}
				break;
			case EItemType::EIT_Ammo:
				DraggedItemCastToPUB = Cast<APickUpBase>(DragDropOp->DraggedItem);
				if (DraggedItemCastToPUB) {
					if (PlayerControllerRef->PickupGoods(DraggedItemCastToPUB)) {
						DragDropOp->DraggedItem->Destroy();
						return 1 || bSuper;
					}

				}

				break;
			case EItemType::EIT_Health:
				DraggedItemCastToPUB = Cast<APickUpBase>(DragDropOp->DraggedItem);
				if (DraggedItemCastToPUB) {
					if (PlayerControllerRef->PickupGoods(DraggedItemCastToPUB)) {
						DragDropOp->DraggedItem->Destroy();
						return 1 || bSuper;
					}

				}

				break;
			case EItemType::EIT_Boost:
				DraggedItemCastToPUB = Cast<APickUpBase>(DragDropOp->DraggedItem);
				if (DraggedItemCastToPUB) {
					if (PlayerControllerRef->PickupGoods(DraggedItemCastToPUB)) {
						DragDropOp->DraggedItem->Destroy();
						return 1 || bSuper;
					}

				}

				break;
			case EItemType::EIT_Helmet:
				

				break;
			case EItemType::EIT_Vest:


				break;
			case EItemType::EIT_Backpack:


				break;
			case EItemType::EIT_Fashion:

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




