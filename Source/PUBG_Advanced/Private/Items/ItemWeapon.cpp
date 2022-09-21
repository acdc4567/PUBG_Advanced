// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemWeapon.h"

AItemWeapon::AItemWeapon() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(Scene);

	Mag = CreateDefaultSubobject<UStaticMeshComponent>("Mag");
	Mag->SetCollisionProfileName("NoCollision");
	Mag->SetupAttachment(SkeletalMesh);

	Muzzle = CreateDefaultSubobject<UStaticMeshComponent>("Muzzle");
	Muzzle->SetCollisionProfileName("NoCollision");
	Muzzle->SetupAttachment(SkeletalMesh);

	Sight = CreateDefaultSubobject<UStaticMeshComponent>("Sight");
	Sight->SetCollisionProfileName("NoCollision");
	Sight->SetupAttachment(SkeletalMesh);

	Foregrip = CreateDefaultSubobject<UStaticMeshComponent>("Foregrip");
	Foregrip->SetCollisionProfileName("NoCollision");
	Foregrip->SetupAttachment(SkeletalMesh);

	ButtStock = CreateDefaultSubobject<UStaticMeshComponent>("ButtStock");
	ButtStock->SetCollisionProfileName("NoCollision");
	ButtStock->SetupAttachment(SkeletalMesh);

	
	ItemWeaponTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemWeapon.DT_ItemWeapon'");
	ItemWeaponTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemWeaponTablePath));




}

void AItemWeapon::OnConstruction(const FTransform& Transform) {

	FSTR_ItemWeapon* ItemWeaponRow = nullptr;
	ItemWeaponRow = ItemWeaponTableObject->FindRow<FSTR_ItemWeapon>(ID, TEXT(""));

	if (ItemWeaponRow) {
		Datas = ItemWeaponRow;
		Init(EItemType::EIT_Weapon,ItemWeaponRow->Name);

		SkeletalMesh->SetSkeletalMesh(ItemWeaponRow->SkeletalMesh);

		Mag->SetStaticMesh(ItemWeaponRow->DefaultMag);
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
		Mag->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Mag")));
		Muzzle->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Muzzle")));

		if (ItemWeaponRow->DefaultSight) {
			Sight->SetStaticMesh(ItemWeaponRow->DefaultSight);
			Sight->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Sight_Default")));

		}
		if (ItemWeaponRow->bCanGrip) {
			Foregrip->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Foregrip")));
		}
		if (ItemWeaponRow->DefaultButtstock) {
			ButtStock->SetStaticMesh(ItemWeaponRow->DefaultButtstock);
			ButtStock->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Socket_Buttstock")));

		}




	}






}
