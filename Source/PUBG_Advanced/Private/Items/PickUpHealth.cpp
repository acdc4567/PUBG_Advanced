// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpHealth.h"
#include "PUBGA_Structs.h"
#include "Kismet/KismetSystemLibrary.h"

APickUpHealth::APickUpHealth() {

	ItemHealthTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemHealth.DT_ItemHealth'");
	ItemHealthTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemHealthTablePath));



}

void APickUpHealth::BeginPlay() {
	Super::BeginPlay();




}

void APickUpHealth::OnConstruction(const FTransform& Transform) {
	FSTR_ItemHealth* ItemHealthRow = nullptr;
	ItemHealthRow = ItemHealthTableObject->FindRow<FSTR_ItemHealth>(ID, TEXT(""));
	if (ItemHealthRow) {
		SingleWeight = ItemHealthRow->Weight;

		InitPickup(EItemType::EIT_Health, ItemHealthRow->Name, "PICK UP ", ItemHealthRow->StaticMesh);



	}



}

int32 APickUpHealth::GetWeight() {
	FSTR_ItemHealth* ItemHealthRow = nullptr;
	ItemHealthRow = ItemHealthTableObject->FindRow<FSTR_ItemHealth>(ID, TEXT(""));

	if (ItemHealthRow) {
		return Amount * SingleWeight;
	}

	return 0;
}
