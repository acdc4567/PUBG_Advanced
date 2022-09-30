// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpBoost.h"

APickUpBoost::APickUpBoost() {
	ItemBoostTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemBoost.DT_ItemBoost'");
	ItemBoostTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemBoostTablePath));


}

void APickUpBoost::OnConstruction(const FTransform& Transform) {
	FSTR_ItemBoost* ItemBoostRow = nullptr;
	ItemBoostRow = ItemBoostTableObject->FindRow<FSTR_ItemBoost>(ID, TEXT(""));
	if (ItemBoostRow) {
		Datas = ItemBoostRow;
		Datas1.Name = Datas->Name;
		Datas1.Icon = Datas->Icon;

		SingleWeight = ItemBoostRow->Weight;

		InitPickup(EItemType::EIT_Boost, ItemBoostRow->Name, "PICK UP ", ItemBoostRow->StaticMesh);



	}

}

int32 APickUpBoost::GetWeight() {

	FSTR_ItemBoost* ItemBoostRow = nullptr;
	ItemBoostRow = ItemBoostTableObject->FindRow<FSTR_ItemBoost>(ID, TEXT(""));

	if (ItemBoostRow) {
		return Amount * SingleWeight;
	}

	return 0;
}
