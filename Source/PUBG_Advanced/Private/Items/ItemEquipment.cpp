// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemEquipment.h"

AItemEquipment::AItemEquipment() {

	StaticMeshx2 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshx2");
	StaticMeshx2->SetCollisionProfileName("NoCollision");
	StaticMeshx2->SetupAttachment(Scene);


	ItemEquipmentTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemEquipment.DT_ItemEquipment'");
	ItemEquipmentTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemEquipmentTablePath));



}

void AItemEquipment::OnConstruction(const FTransform& Transform) {

	FSTR_ItemEquipment* ItemEquipmentRow = nullptr;
	ItemEquipmentRow = ItemEquipmentTableObject->FindRow<FSTR_ItemEquipment>(ID, TEXT(""));
	if (ItemEquipmentRow) {

		Datas = ItemEquipmentRow;
		Init(ItemEquipmentRow->Type, ItemEquipmentRow->Name);
	
		StaticMeshx2->SetStaticMesh(ItemEquipmentRow->StaticMesh);


	

	}





}
