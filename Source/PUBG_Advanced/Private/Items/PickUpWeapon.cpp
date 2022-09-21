// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpWeapon.h"
#include "PUBGA_Structs.h"

APickUpWeapon::APickUpWeapon() {

	ItemWeaponTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeapon.DT_ItemWeapon'");
	ItemWeaponTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponTablePath));


}

void APickUpWeapon::OnConstruction(const FTransform& Transform) {
	FSTR_ItemWeapon* ItemWeaponRow = nullptr;
	
	ItemWeaponRow = ItemWeaponTableObject->FindRow<FSTR_ItemWeapon>(ID, TEXT(""));

	if (ItemWeaponRow) {
		InitPickup(EItemType::EIT_Weapon,ItemWeaponRow->Name,"EQUIP ", ItemWeaponRow->StaticMesh);
	}





}
