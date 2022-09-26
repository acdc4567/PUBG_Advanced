// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerState/PUBGA_PlayerState.h"
#include "Items/PickUpBase.h"
#include "Items/ItemWeapon.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PUBGA_Structs.h"
#include "Items/ItemAmmo.h"
#include "Items/ItemWeaponAcc.h"





APUBGA_PlayerState::APUBGA_PlayerState() {

	ItemEquipmentTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemEquipment.DT_ItemEquipment'");
	ItemEquipmentTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemEquipmentTablePath));

}

void APUBGA_PlayerState::BeginPlay() {

	Super::BeginPlay();

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	
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
	UpdateAmmoObject();
	OnAmmoChanged.Broadcast(1);
}

void APUBGA_PlayerState::SetAmmo762(int32 Value) {
	Ammo762 = Value;
	UpdateAmmoObject();
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
				if (Itemx->ItemType == Item->ItemType && Itemx->ID == Item->ID) {
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

bool APUBGA_PlayerState::CheckBackpackCapacity(int32 AddWeight) {
	
	if (!PlayerControllerRef)return 0;
	int32 TotalCapacity = PlayerControllerRef->DefaultCapacity;
	int32 ItemsWeight=0;
	FSTR_ItemEquipment* ItemEquipmentRow = nullptr;

	for (AItemBase* Equipment : Equipments) {
		if (Equipment->ItemType == EItemType::EIT_Backpack) {
			ItemEquipmentRow = ItemEquipmentTableObject->FindRow<FSTR_ItemEquipment>(Equipment->ID, TEXT(""));
			if (ItemEquipmentRow) {
				TotalCapacity += ItemEquipmentRow->Capacity;
			}

		}
	}

	for (AItemBase* Item : ItemsInBackpack) {
		ItemsWeight += Item->GetWeight();
	}
	if (AddWeight + ItemsWeight <= TotalCapacity) {
		return 1;
	}
	else {
		return 0;
	}

	return 0;

}

void APUBGA_PlayerState::UpdateAmmoObject() {
	if (!PlayerControllerRef)return;
	AItemBase* Ammo1 = nullptr;
	AItemBase* Ammo2 = nullptr;
	AItemAmmo* Ammo1x = nullptr;
	AItemAmmo* Ammo2x = nullptr;
	AItemBase* Ammo1xCastToIB = nullptr;
	AItemBase* Ammo2xCastToIB = nullptr;
	FTransform Transformx;
	Transformx.SetLocation(FVector::ZeroVector);

	for (AItemBase* Item:ItemsInBackpack) {
		if (Item->ItemType == EItemType::EIT_Ammo) {
			if (Item->ID == "1") {
				Ammo1 = Item;
			}
			else {
				Ammo2 = Item;
			}

		}


	}
	if (Ammo556 > 0) {
		if (Ammo1) {
			Ammo1->Amount = GetAmmo556();
		}
		else {
			Ammo1x= GetWorld()->SpawnActorDeferred<AItemAmmo>(AItemAmmo::StaticClass(), Transformx);
			if (Ammo1x) {
				Ammo1x->ID = "1";
				Ammo1x->SN = PlayerControllerRef->GenerateSN();
				Ammo1x->Amount = GetAmmo556();
				Ammo1x->FinishSpawning(Transformx);

				Ammo1xCastToIB = Cast<AItemBase>(Ammo1x);
				if (Ammo1xCastToIB) {
					AddItem(Ammo1xCastToIB);
				}
			
			}
		}
	}
	else {
		if (Ammo1) {
			RemoveItem(Ammo1);
			Ammo1->Destroy();
		}
	}

	if (Ammo762 > 0) {
		if (Ammo2) {
			Ammo2->Amount = GetAmmo762();
		}
		else {
			Ammo2x = GetWorld()->SpawnActorDeferred<AItemAmmo>(AItemAmmo::StaticClass(), Transformx);
			if (Ammo2x) {
				Ammo2x->ID = "2";
				Ammo2x->SN = PlayerControllerRef->GenerateSN();
				Ammo2x->Amount = GetAmmo762();
				Ammo2x->FinishSpawning(Transformx);

				Ammo2xCastToIB = Cast<AItemBase>(Ammo2x);
				if (Ammo2xCastToIB) {
					AddItem(Ammo2xCastToIB);
				}

			}
		}
	}
	else {
		if (Ammo2) {
			RemoveItem(Ammo2);
			Ammo2->Destroy();
		}
	}
}

void APUBGA_PlayerState::UpdateAmmoAmount(FName IDx, bool bAdd, int32 Amountx) {

	if (Amountx == 0) {
		if (IDx == "1") {
			SetAmmo556(0);
		}
		else {
			SetAmmo762(0);
		}

	}
	else {
		if (bAdd) {
			if (IDx == "1") {
				SetAmmo556(GetAmmo556() + Amountx);
			}
			else {
				SetAmmo762(GetAmmo762() + Amountx);
			}

		}
		else {
			if (IDx == "1") {
				SetAmmo556(GetAmmo556() - Amountx);
			}
			else {
				SetAmmo762(GetAmmo762() - Amountx);
			}
		}
	}



}

bool APUBGA_PlayerState::CheckReplaceBackpack(AItemBase* Item) {
	if (!PlayerControllerRef)return 0;
	int32 ItemsWeight=0;
	int32 PickupCapacity = 0;
	TArray<AItemBase*> ItemsInBackpackx = GetItems();
	for (AItemBase* Itemx : ItemsInBackpackx) {
		ItemsWeight += Itemx->GetWeight();
	}
	if (Item) {
		FSTR_ItemEquipment* ItemEquipmentRow = nullptr;
		ItemEquipmentRow = ItemEquipmentTableObject->FindRow<FSTR_ItemEquipment>(Item->ID, TEXT(""));
		if (ItemEquipmentRow) {
			PickupCapacity = ItemEquipmentRow->Capacity;
		}
		
	}
	else {
		PickupCapacity = 0;
	}
	
	


	return PlayerControllerRef->DefaultCapacity + PickupCapacity >= ItemsWeight;
}

void APUBGA_PlayerState::UpdateWeaponAcc(EWeaponPosition Position, EWeaponAccType AccType, AItemWeaponAcc* ItemWeaponAcc) {

	AItemWeapon* Weapon=nullptr;

	switch (Position) {
	case EWeaponPosition::EWP_Left:
		if (Weapon1) {
			Weapon = Weapon1;

		}
		else {
			Weapon = HoldGun;
		}



		break;
	case EWeaponPosition::EWP_Right:
		if (Weapon2) {
			Weapon = Weapon2;

		}
		else {
			Weapon = HoldGun;
		}

		break;
	case EWeaponPosition::EWP_MAX:


		break;
	default:
		break;
	}

	switch (AccType) {
	case EWeaponAccType::EWAT_Sight:
		Weapon->UpdateSight(ItemWeaponAcc);

		break;
	case EWeaponAccType::EWAT_Muzzle:
		Weapon->UpdateMuzzle(ItemWeaponAcc);

		break;
	case EWeaponAccType::EWAT_Foregrip:
		Weapon->UpdateForegrip(ItemWeaponAcc);

		break;
	case EWeaponAccType::EWAT_Mag:
		Weapon->UpdateMag(ItemWeaponAcc);

		break;
	case EWeaponAccType::EWAT_Buttstock:
		Weapon->UpdateButtstock(ItemWeaponAcc);

		break;
	case EWeaponAccType::EWAT_MAX:


		break;
	default:
		break;
	}

	bool bCheckValid = 0;
	if (ItemWeaponAcc) {
		bCheckValid = 1;
	}
	else {
		bCheckValid = 0;
	}

	OnWeaponAccChanged.Broadcast(Weapon,!bCheckValid,ItemWeaponAcc,AccType);


}


int32 APUBGA_PlayerState::GetAmmoAmount(FName IDName) {

	if (IDName=="1") {
		return GetAmmo556();

	}
	else {
		return GetAmmo762();
	}

}










