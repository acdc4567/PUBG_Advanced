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
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount);
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
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount);
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
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount);
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
					GoodsWidget->SetContents(ItemInBackpack, Icon, Name, Amount);
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
