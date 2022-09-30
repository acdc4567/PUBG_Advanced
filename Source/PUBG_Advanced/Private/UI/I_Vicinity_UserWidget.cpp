// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Vicinity_UserWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Items/ItemBase.h"
#include "Items/PickUpBase.h"
#include "Items/PickUpWeapon.h"
#include "UI/I_GoodsItem_UserWidget.h"


void UI_Vicinity_UserWidget::UpdateList(bool bIsOnHand) {

	if (!PlayerControllerRef)return;
	
	int32 Amount = 0;
	FName Name;
	UTexture2D* Icon;
	ClearChildrens();
	TArray<APickUpBase*> ItemsInRange;
	ItemsInRange = PlayerControllerRef->GetItemsInRange();
	for (APickUpBase* ItemInRange : ItemsInRange) {
		Amount = ItemInRange->Amount;

		APickUpWeapon* ItemCastToPUWeapon = nullptr;
		AItemBase* ItemWeaponCastToIB = nullptr;
		switch (ItemInRange->ItemType) {
		case EItemType::EIT_Weapon:
			ItemCastToPUWeapon = Cast<APickUpWeapon>(ItemInRange);
			if (ItemCastToPUWeapon) {
				
				Name= ItemCastToPUWeapon->Datas->Name;
				Icon= ItemCastToPUWeapon->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {
					//UE_LOG(LogTemp, Warning, TEXT("GotIt"));
					AddChildrens(ItemWeaponCastToIB,Icon,Name,Amount);
				}
				
				
			}
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

bool UI_Vicinity_UserWidget::InitializePlayerController(APUBGA_PlayerController* APC) {
	
	if (APC) {
		PlayerControllerRef = APC;
		PlayerControllerRef->ItemsInRangeChangeSignature.AddDynamic(this, &UI_Vicinity_UserWidget::UpdateList);
		return 1;
	}
	else {
		return 0;
	}

	return 0;


}
