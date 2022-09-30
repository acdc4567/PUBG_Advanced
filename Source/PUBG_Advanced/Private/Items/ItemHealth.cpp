// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemHealth.h"

AItemHealth::AItemHealth() {
	ItemHealthTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemHealth.DT_ItemHealth'");
	ItemHealthTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemHealthTablePath));


}

void AItemHealth::OnConstruction(const FTransform& Transform) {

	FSTR_ItemHealth* ItemHealthRow = nullptr;
	ItemHealthRow = ItemHealthTableObject->FindRow<FSTR_ItemHealth>(ID, TEXT(""));
	if (ItemHealthRow) {
		Datas = ItemHealthRow;
		Datas1.Name = Datas->Name;
		Datas1.Icon = Datas->Icon;
		Init(EItemType::EIT_Health, Datas->Name);
		UseTime = Datas->UseTime;
	
	}


}

int32 AItemHealth::GetWeight() {
	if (Datas) {
		return Amount * Datas->Weight;
	}


	return 0;
}
