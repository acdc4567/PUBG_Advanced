// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/Inventory_UserWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemBase.h"
#include "Items/PickUpBase.h"
#include "Items/PickUpWeapon.h"
#include "Items/PickUpWeaponAcc.h"
#include "Items/PickUpBoost.h"
#include "Items/PickUpEquipment.h"
#include "Items/PickUpFashion.h"
#include "Items/PickUpHealth.h"
#include "Items/PickUpAmmo.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Items/ItemWeaponAcc.h"
#include "Items/ItemHealth.h"
#include "Items/ItemBoost.h"
#include "Items/ItemAmmo.h"


void UInventory_UserWidget::ItemsInRangeChange_Handle(bool bIsOnHand) {
	

}

void UInventory_UserWidget::UpdateList(bool bIsOnHand) {

	if (!PlayerControllerRef)return;

	int32 Amount = 0;
	FName Name;
	UTexture2D* Icon=nullptr;
	ClearChildrens();
	TArray<APickUpBase*> ItemsInRange;
	ItemsInRange = PlayerControllerRef->GetItemsInRange();
	for (APickUpBase* ItemInRange : ItemsInRange) {
		Amount = ItemInRange->Amount;
		AItemBase* ItemWeaponCastToIB = nullptr;
		APickUpWeapon* ItemCastToPUWeapon = nullptr;
		APickUpWeaponAcc* ItemCastToPUWeaponAcc = nullptr;
		APickUpBoost* ItemCastToPUBoost = nullptr;
		APickUpHealth* ItemCastToPUHealth = nullptr;
		APickUpEquipment* ItemCastToPUEquipment = nullptr;
		APickUpFashion* ItemCastToPUFashion = nullptr;
		APickUpAmmo* ItemCastToPUAmmo = nullptr;

		switch (ItemInRange->ItemType) {
		case EItemType::EIT_Weapon:
			ItemCastToPUWeapon = Cast<APickUpWeapon>(ItemInRange);
			if (ItemCastToPUWeapon) {

				Name = ItemCastToPUWeapon->Datas->Name;
				Icon = ItemCastToPUWeapon->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {
					
					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}
			break;
		case EItemType::EIT_Accessories:
			ItemCastToPUWeaponAcc = Cast<APickUpWeaponAcc>(ItemInRange);
			if (ItemCastToPUWeaponAcc) {

				Name = ItemCastToPUWeaponAcc->Datas->Name;
				Icon = ItemCastToPUWeaponAcc->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Ammo:
			ItemCastToPUAmmo = Cast<APickUpAmmo>(ItemInRange);
			if (ItemCastToPUAmmo) {

				Name = ItemCastToPUAmmo->Datas->Name;
				Icon = ItemCastToPUAmmo->Datas->Icon;
				
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Health:
			ItemCastToPUHealth = Cast<APickUpHealth>(ItemInRange);
			if (ItemCastToPUHealth) {

				Name = ItemCastToPUHealth->Datas->Name;
				Icon = ItemCastToPUHealth->Datas->Icon;

				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Boost:
			ItemCastToPUBoost = Cast<APickUpBoost>(ItemInRange);
			if (ItemCastToPUBoost) {

				Name = ItemCastToPUBoost->Datas->Name;
				Icon = ItemCastToPUBoost->Datas->Icon;

				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Helmet:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Vest:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Backpack:
			ItemCastToPUEquipment = Cast<APickUpEquipment>(ItemInRange);
			if (ItemCastToPUEquipment) {

				Name = ItemCastToPUEquipment->Datas->Name;
				Icon = ItemCastToPUEquipment->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
				}


			}

			break;
		case EItemType::EIT_Fashion:
			ItemCastToPUFashion = Cast<APickUpFashion>(ItemInRange);
			if (ItemCastToPUFashion) {

				Name = ItemCastToPUFashion->Datas->Name;
				Icon = ItemCastToPUFashion->Datas->Icon;
				Amount = 0;
				ItemWeaponCastToIB = Cast<AItemBase>(ItemInRange);
				if (ItemWeaponCastToIB) {

					AddChildrens(ItemWeaponCastToIB, Icon, Name, Amount);
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

void UInventory_UserWidget::UpdateBackpackList(AItemBase* Item, bool bIsAdd) {

	if (!PlayerControllerRef)return;
	if (!PlayerStateRef)return;
	UE_LOG(LogTemp, Warning, TEXT("GetIt"));
	int32 Amount = 0;
	FName Name;
	UTexture2D* Icon=nullptr;
	ClearChildrenxs();
	TArray<AItemBase*> ItemsInBackpack;
	ItemsInBackpack = PlayerStateRef->GetItems();

	AItemWeaponAcc* ItemCastToIBWeaponAcc = nullptr;
	AItemBoost* ItemCastToIBBoost = nullptr;
	AItemHealth* ItemCastToIBHealth = nullptr;
	AItemAmmo* ItemCastToIBAmmo = nullptr;


	for (AItemBase* ItemInBackpack : ItemsInBackpack) {
		Amount = ItemInBackpack->Amount;

		switch (ItemInBackpack->ItemType) {
		case EItemType::EIT_Weapon:


			break;
		case EItemType::EIT_Accessories:
			ItemCastToIBWeaponAcc = Cast<AItemWeaponAcc>(ItemInBackpack);
			if (ItemCastToIBWeaponAcc) {
				Name = ItemCastToIBWeaponAcc->Datas->Name;
				Icon = ItemCastToIBWeaponAcc->Datas->Icon;
				Amount = 0;
				AddChildrenxs(ItemInBackpack, Icon, Name, Amount);
			}

			break;
		case EItemType::EIT_Ammo:
			ItemCastToIBAmmo = Cast<AItemAmmo>(ItemInBackpack);
			if (ItemCastToIBAmmo) {
				Name = ItemCastToIBAmmo->Datas->Name;
				Icon = ItemCastToIBAmmo->Datas->Icon;
				AddChildrenxs(ItemInBackpack, Icon, Name, Amount);
			}

			break;
		case EItemType::EIT_Health:
			ItemCastToIBHealth = Cast<AItemHealth>(ItemInBackpack);
			if (ItemCastToIBHealth) {
				Name = ItemCastToIBHealth->Datas->Name;
				Icon = ItemCastToIBHealth->Datas->Icon;
				AddChildrenxs(ItemInBackpack, Icon, Name, Amount);
			}

			break;
		case EItemType::EIT_Boost:
			ItemCastToIBBoost = Cast<AItemBoost>(ItemInBackpack);
			if (ItemCastToIBBoost) {
				Name = ItemCastToIBBoost->Datas->Name;
				Icon = ItemCastToIBBoost->Datas->Icon;
				AddChildrenxs(ItemInBackpack, Icon, Name, Amount);
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


bool UInventory_UserWidget::InitializePlayerController(APUBGA_PlayerController* APC) {
	if (PlayerControllerRef)return 1;
	if (APC) {
		PlayerControllerRef = APC;
		//PlayerControllerRef->ItemsInRangeChangeSignature.AddDynamic(this, &UInventory_UserWidget::UpdateList);
		return 1;
	}
	else {
		return 0;
	}
	
	return 0;
}

bool UInventory_UserWidget::InitializePlayerState(APUBGA_PlayerState* APS) {
	if (!PlayerControllerRef)return 0;
	if (PlayerStateRef)return 1;
	if (PlayerControllerRef->GetPlayerStateRef()) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		UE_LOG(LogTemp, Warning, TEXT("GetIt111"));
		if (PlayerStateRef) {
			PlayerStateRef->OnItemsChanged.AddDynamic(this, &UInventory_UserWidget::UpdateBackpackList);
			
			return 1;
		}
		
	}
	else {
		return 0;
	}

	return 0;
}
