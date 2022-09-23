// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerState/PUBGA_PlayerState.h"
#include "Items/PickUpBase.h"
#include "Items/ItemWeapon.h"
#include "Items/ItemBase.h"





APUBGA_PlayerState::APUBGA_PlayerState() {


}

AItemWeapon* APUBGA_PlayerState::GetWeapon1() {
	if (Weapon1) {
		return Weapon1;
	}
	
	return nullptr;
}

AItemWeapon* APUBGA_PlayerState::GetWeapon2() {
	if (Weapon2) {
		return Weapon2;
	}
	return nullptr;
}

AItemWeapon* APUBGA_PlayerState::GetHoldGun() {
	if (HoldGun) {
		return HoldGun;
	}
	return nullptr;
}

int32 APUBGA_PlayerState::GetAmmo556() {
	
	return Ammo556;
}

int32 APUBGA_PlayerState::GetAmmo762() {
	return Ammo762;
}

float APUBGA_PlayerState::GetHealthPoint() {
	return HealthPoint;
}

float APUBGA_PlayerState::GetEnergyPoint() {
	return EnergyPoint;
}

TArray<AItemBase*> APUBGA_PlayerState::GetEquipments() {
	return Equipments;
}

TArray<AItemBase*> APUBGA_PlayerState::GetFashions() {
	return Fashions;
}

TArray<AItemBase*> APUBGA_PlayerState::GetItems() {
	return ItemsInBackpack;
}

void APUBGA_PlayerState::SetWeapon1(AItemWeapon* WeaponToSet) {
	Weapon1 = WeaponToSet;
	OnWeaponChanged.Broadcast(Weapon1, EWeaponPosition::EWP_Left, 0);
}

void APUBGA_PlayerState::SetWeapon2(AItemWeapon* WeaponToSet) {
	Weapon2 = WeaponToSet;
	OnWeaponChanged.Broadcast(Weapon2, EWeaponPosition::EWP_Right, 0);
}

void APUBGA_PlayerState::SetHoldGun(AItemWeapon* WeaponToSet) {

	HoldGun = WeaponToSet;
	if (HoldGun) {
		OnWeaponChanged.Broadcast(HoldGun, HoldGun->Position, 1);
	}
	else {
		OnWeaponChanged.Broadcast(HoldGun, EWeaponPosition::EWP_Left, 1);
	}
	

}

void APUBGA_PlayerState::SetAmmo556(int32 Value) {
	Ammo556 = Value;
	OnAmmoChanged.Broadcast(1);
}

void APUBGA_PlayerState::SetAmmo762(int32 Value) {
	Ammo762 = Value;
	OnAmmoChanged.Broadcast(1);

}

void APUBGA_PlayerState::SetHealthPoint(float Value) {
	HealthPoint = Value;
	OnHealthChanged.Broadcast(HealthPoint);
}

void APUBGA_PlayerState::SetEnergyPoint(float Value) {
	EnergyPoint = Value;
	OnEnergyChanged.Broadcast(EnergyPoint);
}

void APUBGA_PlayerState::AddEquipment(AItemBase* Equipment) {
	if (Equipment) {
		Equipments.Add(Equipment);
		OnEquipmentChanged.Broadcast(Equipment,1);
	}
	
}

void APUBGA_PlayerState::AddFashion(AItemBase* Fashion) {
	if (Fashion) {
		Fashions.Add(Fashion);
		OnFashionChanged.Broadcast(Fashion, 1);
	
	}


}

void APUBGA_PlayerState::AddItem(AItemBase* Item) {
	bool bIsFound = 0;
	if (Item) {
		if (Item->ItemType == EItemType::EIT_Health || Item->ItemType == EItemType::EIT_Boost) {

			for (auto Itemx : ItemsInBackpack) {
				if (Itemx->ItemType == Item->ItemType&&Itemx->ID==Item->ID) {
					Itemx->Amount += Item->Amount;
					bIsFound = 1;
					OnItemsChanged.Broadcast(Itemx, 1);
					break;
				}
			}

			if (!bIsFound) {
				ItemsInBackpack.Add(Item);
				OnItemsChanged.Broadcast(Item, 1);
			}
		}
		else {
			ItemsInBackpack.Add(Item);
			OnItemsChanged.Broadcast(Item, 1);
		}

	}


}

bool APUBGA_PlayerState::RemoveEquipment(AItemBase* Equipment) {
	int32 TempArrayIndex=0;
	if (Equipment) {
		bool bFoundEq=Equipments.Find(Equipment, TempArrayIndex);
		if (bFoundEq) {
			Equipments.RemoveAt(TempArrayIndex);
		
			OnEquipmentChanged.Broadcast(Equipment, 0);
			return 1;
		}
		

	}

	return false;
}

bool APUBGA_PlayerState::RemoveFashion(AItemBase* Fashion) {

	int32 TempArrayIndex = 0;
	if (Fashion) {
		bool bFoundFas = Fashions.Find(Fashion, TempArrayIndex);
		if (bFoundFas) {
			Fashions.RemoveAt(TempArrayIndex);

			OnFashionChanged.Broadcast(Fashion, 0);
			return 1;
		}


	}

	return false;
}

bool APUBGA_PlayerState::RemoveItem(AItemBase* Item) {

	int32 TempArrayIndex = 0;
	if (Item) {
		bool bFoundItem = ItemsInBackpack.Find(Item, TempArrayIndex);
		if (bFoundItem) {
			ItemsInBackpack.RemoveAt(TempArrayIndex);

			OnItemsChanged.Broadcast(Item, 0);
			return 1;
		}


	}



	return false;
}
