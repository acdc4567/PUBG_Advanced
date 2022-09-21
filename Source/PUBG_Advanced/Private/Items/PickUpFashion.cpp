// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpFashion.h"
#include "PUBGA_Structs.h"
#include "Kismet/KismetSystemLibrary.h"


APickUpFashion::APickUpFashion() {

	ItemFashionTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemFashion.DT_ItemFashion'");
	ItemFashionTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemFashionTablePath));

}

void APickUpFashion::BeginPlay() {

	Super::BeginPlay();

	FVector Origin, BoxExtent;
	float SphereRadius;
	UKismetSystemLibrary::GetComponentBounds(StaticMeshx1, Origin, BoxExtent, SphereRadius);

	FVector BoxExtentZ = FVector(0.f, 0.f, BoxExtent.Z);
	AddActorLocalOffset(BoxExtentZ);


}

void APickUpFashion::OnConstruction(const FTransform& Transform) {

	FSTR_ItemFashion* ItemFashionRow = nullptr;
	ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));
	if (ItemFashionRow) {
		FashionType = ItemFashionRow->Type;

		InitPickup(EItemType::EIT_Fashion, ItemFashionRow->Name, "EQUIP ", ItemFashionRow->StaticMesh);
		if (FashionType!=EFashionType::EFT_Shoes) {
			StaticMeshx1->SetWorldScale3D(FVector(1.f, .1f, 1.f));

			StaticMeshx1->SetWorldRotation(FRotator(0.f, 0.f, -90.f));

		}
		
	}




}
