// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemAmmo.h"

AItemAmmo::AItemAmmo() {

	ItemAmmoTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemAmmo.DT_ItemAmmo'");
	ItemAmmoTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemAmmoTablePath));

}



void AItemAmmo::OnConstruction(const FTransform& Transform) {

	FSTR_ItemAmmo* ItemAmmoRow = nullptr;
	ItemAmmoRow = ItemAmmoTableObject->FindRow<FSTR_ItemAmmo>(ID, TEXT(""));
	if (ItemAmmoRow) {
		Datas = ItemAmmoRow;
		Datas1.Name = Datas->Name;
		Datas1.Icon = Datas->Icon;
		Init(EItemType::EIT_Ammo, ItemAmmoRow->Name);


	}


}

int32 AItemAmmo::GetWeight() {
	if (Datas) {
		return Amount * Datas->Weight;

	}

	return 0;
}
