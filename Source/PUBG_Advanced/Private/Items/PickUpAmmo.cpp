// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpAmmo.h"
#include "PUBGA_Structs.h"

APickUpAmmo::APickUpAmmo() {

	ItemAmmoTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemAmmo.DT_ItemAmmo'");
	ItemAmmoTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemAmmoTablePath));


}

void APickUpAmmo::OnConstruction(const FTransform& Transform) {

	FSTR_ItemAmmo* ItemAmmoRow = nullptr;
	ItemAmmoRow = ItemAmmoTableObject->FindRow<FSTR_ItemAmmo>(ID, TEXT(""));

	if (ItemAmmoRow) {
		if (Amount == 0) {
			Amount = ItemAmmoRow->PickupAmount;
			
		}
		SingleWeight = ItemAmmoRow->Weight;
		InitPickup(EItemType::EIT_Ammo, ItemAmmoRow->Name, "PICK UP ", ItemAmmoRow->PickupMesh);


	}





}

int32 APickUpAmmo::GetWeight() {
	FSTR_ItemAmmo* ItemAmmoRow = nullptr;
	ItemAmmoRow = ItemAmmoTableObject->FindRow<FSTR_ItemAmmo>(ID, TEXT(""));

	if (ItemAmmoRow) {
		return Amount * SingleWeight;
	}


	return 0;
}
