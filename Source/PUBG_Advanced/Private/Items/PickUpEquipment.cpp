// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpEquipment.h"
#include "PUBGA_Structs.h"
#include "Kismet/KismetSystemLibrary.h"

APickUpEquipment::APickUpEquipment() {

	ItemEquipmentTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemEquipment.DT_ItemEquipment'");
	ItemEquipmentTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemEquipmentTablePath));




}

void APickUpEquipment::BeginPlay() {

	Super::BeginPlay();
	FVector Origin, BoxExtent;
	float SphereRadius;
	UKismetSystemLibrary::GetComponentBounds(StaticMeshx1, Origin, BoxExtent, SphereRadius);

	if (EquipmentType == EItemType::EIT_Helmet) {
		
		FVector BoxExtentZ = FVector(0.f, 0.f, BoxExtent.Z * 2.f);
		AddActorLocalOffset(BoxExtentZ);


	}
	else {
		FVector BoxExtentZ = FVector(0.f, 0.f, BoxExtent.Z );
		AddActorLocalOffset(BoxExtentZ);

	}


}

void APickUpEquipment::OnConstruction(const FTransform& Transform) {

	FSTR_ItemEquipment* ItemEquipmentRow = nullptr;
	ItemEquipmentRow = ItemEquipmentTableObject->FindRow<FSTR_ItemEquipment>(ID, TEXT(""));

	if (ItemEquipmentRow) {
		EquipmentType = ItemEquipmentRow->Type;

		InitPickup(EquipmentType, ItemEquipmentRow->Name, "SWITCH TO ", ItemEquipmentRow->StaticMesh);
		if (ItemEquipmentRow->Type == EItemType::EIT_Vest) {
			StaticMeshx1->SetWorldScale3D(FVector(1.f, .1f, 1.f));
			
			StaticMeshx1->SetWorldRotation(FRotator(0.f,0.f,-90.f),0,nullptr,ETeleportType::TeleportPhysics);
		}
		if (ItemEquipmentRow->Type == EItemType::EIT_Backpack) {
			StaticMeshx1->SetWorldScale3D(FVector(1.f, .1f, 1.f));

			StaticMeshx1->SetWorldRotation(FRotator(0.f, 0.f, 90.f), 0, nullptr, ETeleportType::TeleportPhysics);
		}
	}


}


