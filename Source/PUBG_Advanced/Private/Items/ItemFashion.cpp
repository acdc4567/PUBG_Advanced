// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemFashion.h"

AItemFashion::AItemFashion() {
	ItemFashionTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemFashion.DT_ItemFashion'");
	ItemFashionTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemFashionTablePath));



}

void AItemFashion::OnConstruction(const FTransform& Transform) {
	FSTR_ItemFashion* ItemFashionRow = nullptr;
	if (ID != " " || ID != "") {
		ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));

	}
	if (ItemFashionRow) {
		Datas = ItemFashionRow;
		Datas1.Icon = Datas->Icon;
		FashionType = Datas->Type;
		Init(EItemType::EIT_Fashion, Datas->Name);
		
	}



}
