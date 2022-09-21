// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemWeaponAcc.h"

AItemWeaponAcc::AItemWeaponAcc() {

	ItemWeaponAccTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeaponAcc.DT_ItemWeaponAcc'");
	ItemWeaponAccTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponAccTablePath));




}

void AItemWeaponAcc::OnConstruction(const FTransform& Transform) {

	FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;
	ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(ID, TEXT(""));
	
	
	if (ItemWeaponAccRow) {
		Datas = ItemWeaponAccRow;
		Init(EItemType::EIT_Accessories,ItemWeaponAccRow->Name);
		AccType = ItemWeaponAccRow->Type;

	}


}

int32 AItemWeaponAcc::GetWeight() {
	
	return Datas->Weight;
	
}
