// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpWeaponAcc.h"
#include "PUBGA_Structs.h"
#include "Kismet/KismetSystemLibrary.h"

APickUpWeaponAcc::APickUpWeaponAcc() {

	ItemWeaponAccTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeaponAcc.DT_ItemWeaponAcc'");
	ItemWeaponAccTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponAccTablePath));



}

void APickUpWeaponAcc::BeginPlay() {

	Super::BeginPlay();

	if (AccType != EWeaponAccType::EWAT_Sight) {

		FVector Origin, BoxExtent;
		float SphereRadius;
		UKismetSystemLibrary::GetComponentBounds(StaticMeshx1, Origin, BoxExtent, SphereRadius);
	
		FVector BoxExtentZ = FVector(0.f, 0.f, BoxExtent.Z);
		AddActorLocalOffset(BoxExtentZ);

	
	
	}
	


}


void APickUpWeaponAcc::OnConstruction(const FTransform& Transform) {

	FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;

	ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(ID, TEXT(""));

	
	if (ItemWeaponAccRow) {
		Datas = ItemWeaponAccRow;
		Datas1.Name = Datas->Name;
		Datas1.Icon = Datas->Icon;

		InitPickup(EItemType::EIT_Accessories, ItemWeaponAccRow->Name, "PICK UP ", ItemWeaponAccRow->StaticMesh);
		AccType = ItemWeaponAccRow->Type;

	}

	FRotator WorldRot = FRotator(0.f, 0.f, -90.f);

	switch (AccType) {
	case EWeaponAccType::EWAT_Sight:
		break;
	case EWeaponAccType::EWAT_Muzzle:
		break;
	case EWeaponAccType::EWAT_Foregrip:
		StaticMeshx1->SetWorldRotation(WorldRot);
		break;
	case EWeaponAccType::EWAT_Mag:
		StaticMeshx1->SetWorldRotation(WorldRot);
		break;
	case EWeaponAccType::EWAT_Buttstock:
		StaticMeshx1->SetWorldRotation(WorldRot);
		break;
	case EWeaponAccType::EWAT_MAX:
		break;
	default:
		break;
	}



}

int32 APickUpWeaponAcc::GetWeight() {
	FSTR_ItemWeaponAcc* ItemWeaponAccRow = nullptr;

	ItemWeaponAccRow = ItemWeaponAccTableObject->FindRow<FSTR_ItemWeaponAcc>(ID, TEXT(""));
	if (ItemWeaponAccRow) {
		return ItemWeaponAccRow->Weight;
	}
	return 0;
}
