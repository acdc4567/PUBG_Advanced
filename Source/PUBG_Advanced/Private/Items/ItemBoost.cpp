// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemBoost.h"

AItemBoost::AItemBoost() {
	ItemBoostTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemBoost.DT_ItemBoost'");
	ItemBoostTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemBoostTablePath));


}

void AItemBoost::OnConstruction(const FTransform& Transform) {
	FSTR_ItemBoost* ItemBoostRow = nullptr;
	ItemBoostRow = ItemBoostTableObject->FindRow<FSTR_ItemBoost>(ID, TEXT(""));
	if (ItemBoostRow) {
		Datas = ItemBoostRow;
		Datas1.Name = Datas->Name;
		Datas1.Icon = Datas->Icon;
		Init(EItemType::EIT_Boost, Datas->Name);
		UseTime = Datas->UseTime;

	}


}

int32 AItemBoost::GetWeight() {
	if (Datas) {
		return Amount * Datas->Weight;
	}


	return int32();
}
