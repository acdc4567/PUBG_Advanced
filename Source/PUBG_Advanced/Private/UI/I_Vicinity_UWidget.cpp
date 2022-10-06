// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Vicinity_UWidget.h"
#include "UI/I_GoodsItem_UserWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ScrollBox.h"
#include "Items/PickUpBase.h"
#include "Items/PickUpWeapon.h"
#include "Items/PickUpWeaponAcc.h"
#include "Items/PickUpAmmo.h"
#include "Items/PickUpBoost.h"
#include "Items/PickUpEquipment.h"
#include "Items/PickUpFashion.h"
#include "Items/PickUpHealth.h"
#include "UI/I_DragDropOperation.h"






void UI_Vicinity_UWidget::UpdateList(bool bIsOnHand) {
	if (!PlayerControllerRef)return;
	if (!GoodsItemWidgetClass)return;

	GoodsItemList->ClearChildren();
	int32 Amount = 0;
	FName Name;
	UTexture2D* Icon = nullptr;

	AItemBase* PUItemCastToIB = nullptr;
	
	APickUpWeapon* ItemCastToPUWeapon = nullptr;
	APickUpWeaponAcc* ItemCastToPUWeaponAcc = nullptr;
	APickUpBoost* ItemCastToPUBoost = nullptr;
	APickUpHealth* ItemCastToPUHealth = nullptr;
	APickUpAmmo* ItemCastToPUAmmo = nullptr;
	APickUpEquipment* ItemCastToPUEquipment = nullptr;
	APickUpFashion* ItemCastToPUFashion = nullptr;

	UI_GoodsItem_UserWidget* GoodsWidget = nullptr;

	TArray<APickUpBase*> ItemsInRange= PlayerControllerRef->GetItemsInRange();
	for (APickUpBase* ItemInRange : ItemsInRange) {
		Amount = ItemInRange->Amount;

		switch (ItemInRange->ItemType) {
		case EItemType::EIT_Weapon:
			ItemCastToPUWeapon = Cast<APickUpWeapon>(ItemInRange);
			if (ItemCastToPUWeapon) {

				Name = ItemCastToPUWeapon->Datas->Name;
				Icon = ItemCastToPUWeapon->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount,EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Accessories:
			ItemCastToPUWeaponAcc = Cast<APickUpWeaponAcc>(ItemInRange);
			if (ItemCastToPUWeaponAcc) {

				Name = ItemCastToPUWeaponAcc->Datas->Name;
				Icon = ItemCastToPUWeaponAcc->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Ammo:
			ItemCastToPUAmmo = Cast<APickUpAmmo>(ItemInRange);
			if (ItemCastToPUAmmo) {

				Name = ItemCastToPUAmmo->Datas->Name;
				Icon = ItemCastToPUAmmo->Datas->Icon;
				
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Health:
			ItemCastToPUHealth = Cast<APickUpHealth>(ItemInRange);
			if (ItemCastToPUHealth) {

				Name = ItemCastToPUHealth->Datas->Name;
				Icon = ItemCastToPUHealth->Datas->Icon;

				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Boost:
			ItemCastToPUBoost = Cast<APickUpBoost>(ItemInRange);
			if (ItemCastToPUBoost) {

				Name = ItemCastToPUBoost->Datas->Name;
				Icon = ItemCastToPUBoost->Datas->Icon;

				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Helmet:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Vest:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Backpack:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_Fashion:
			ItemCastToPUFashion = Cast<APickUpFashion>(ItemInRange);
			if (ItemCastToPUFashion) {

				Name = ItemCastToPUFashion->Datas->Name;
				Icon = ItemCastToPUFashion->Datas->Icon;
				Amount = 0;
				PUItemCastToIB = Cast<AItemBase>(ItemInRange);
				GoodsWidget = CreateWidget<UI_GoodsItem_UserWidget>(GetWorld(), GoodsItemWidgetClass);
				if (GoodsWidget && PUItemCastToIB) {
					GoodsWidget->SetContents(PUItemCastToIB, Icon, Name, Amount, EInventoryLocationx::EIL_VicinityList);
					GoodsItemList->AddChild(GoodsWidget);
				}


			}

			break;
		case EItemType::EIT_MAX:
			break;
		default:
			break;
		}

	}

}



void UI_Vicinity_UWidget::NativeConstruct() {
	Super::NativeConstruct();


	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {

		PlayerControllerRef->ItemsInRangeChangeSignature.AddDynamic(this,&UI_Vicinity_UWidget::UpdateList);
		UpdateList(0);

	}


}

void UI_Vicinity_UWidget::NativeDestruct() {
	Super::NativeDestruct();
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {

		PlayerControllerRef->ItemsInRangeChangeSignature.RemoveDynamic(this, &UI_Vicinity_UWidget::UpdateList);


	}




}

bool UI_Vicinity_UWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	bool bSuper = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (!PlayerControllerRef)return 0;
	UI_DragDropOperation* DragDropOp = Cast<UI_DragDropOperation>(InOperation);
	if (DragDropOp) {
		

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
			




			break;
		case EInventoryLocationx::EIL_BackpackList:
			PlayerControllerRef->DiscardItem(DragDropOp->DraggedItem);

			return 1||bSuper;



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




