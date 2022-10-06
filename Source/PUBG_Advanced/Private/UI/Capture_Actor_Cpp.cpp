// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/Capture_Actor_Cpp.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Items/ItemBase.h"
#include "Items/ItemEquipment.h"
#include "Items/ItemWeapon.h"
#include "Items/ItemWeaponAcc.h"
#include "Items/ItemFashion.h"
#include "Engine/SkeletalMeshSocket.h"
#include "PUBGA_Structs.h"
#include "Player/PUBGA_Character.h"




ACapture_Actor_Cpp::ACapture_Actor_Cpp() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(GetRootComponent());

	SKM_Hair = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Hair");
	//SKM_Hair->AddRelativeLocation(FVector(1.f, 1.f, 1.f));
	SKM_Hair->SetupAttachment(SkeletalMesh);

	SKM_UnderwearTop = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_UnderwearTop");
	SKM_UnderwearTop->SetupAttachment(SkeletalMesh);

	SKM_UnderwearBottom = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_UnderwearBottom");
	SKM_UnderwearBottom->SetupAttachment(SkeletalMesh);

	SKM_ClothTop = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_ClothTop");
	SKM_ClothTop->SetupAttachment(SkeletalMesh);

	SKM_ClothBottom = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_ClothBottom");
	SKM_ClothBottom->SetupAttachment(SkeletalMesh);

	SKM_Whole = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Whole");
	SKM_Whole->SetupAttachment(SkeletalMesh);

	SKM_Shoes = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Shoes");
	SKM_Shoes->SetupAttachment(SkeletalMesh);

	ItemFashionTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemFashion.DT_ItemFashion'");
	ItemFashionTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemFashionTablePath));



}

void ACapture_Actor_Cpp::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	
	if (PlayerStateRef->GetHoldGun()) {
		bHoldWeapon = 1;
	}
	else {
		bHoldWeapon = 0;
	}
	
	if (bHoldWeapon) {
		
		
		PlayHoldGunAnim();
	}
	else {
		PlayNoGunAnim();
	}


}

void ACapture_Actor_Cpp::BeginPlay() {
	Super::BeginPlay();

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerCharacterRef=Cast<APUBGA_Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnEquipmentChanged.AddDynamic(this, &ACapture_Actor_Cpp::UpdateEquipment);
			PlayerStateRef->OnFashionChanged.AddDynamic(this, &ACapture_Actor_Cpp::UpdateFashionx);
			PlayerStateRef->OnWeaponChanged.AddDynamic(this, &ACapture_Actor_Cpp::UpdateWeaponx);
			PlayerStateRef->OnWeaponAccChanged.AddDynamic(this, &ACapture_Actor_Cpp::UpdateWeaponAcc);

			UpdateFashionx(nullptr,0);
			UpdateEquipment(nullptr,0);
			UpdateWeaponx(nullptr,EWeaponPosition::EWP_Left,0	);
			
			
		}
	}


}

void ACapture_Actor_Cpp::Destroyed() {

	Super::Destroyed();

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerCharacterRef = Cast<APUBGA_Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnEquipmentChanged.RemoveDynamic(this, &ACapture_Actor_Cpp::UpdateEquipment);
			ClearEquipments();
			PlayerStateRef->OnFashionChanged.RemoveDynamic(this, &ACapture_Actor_Cpp::UpdateFashionx);
			PlayerStateRef->OnWeaponChanged.RemoveDynamic(this, &ACapture_Actor_Cpp::UpdateWeaponx);
			ClearWeapons();
			PlayerStateRef->OnWeaponAccChanged.RemoveDynamic(this, &ACapture_Actor_Cpp::UpdateWeaponAcc);
			
		}
	}


}





void ACapture_Actor_Cpp::UpdateEquipment(AItemBase* Equipment, bool bIsAdd) {

	if (!PlayerStateRef)return;
	if (!PlayerControllerRef)return;
	ClearEquipments();
	TArray<AItemBase*> Equipments = PlayerStateRef->GetEquipments();
	for (AItemBase* Equipmentx : Equipments) {

		if (Equipmentx->ItemType == EItemType::EIT_Helmet ) {
			HelmetObj= SpawnActorx(EItemType::EIT_Helmet, Equipmentx->ID, "3DCharacter_Helmet");
			Attach(HelmetObj,PlayerControllerRef->HelmetName);
			
		}
		if (Equipmentx->ItemType == EItemType::EIT_Vest) {
			VestObj = SpawnActorx(EItemType::EIT_Vest, Equipmentx->ID, "3DCharacter_Vest");
			Attach(VestObj, PlayerControllerRef->VestName);
			
		}
		if (Equipmentx->ItemType == EItemType::EIT_Backpack) {
			BackpackObj = SpawnActorx(EItemType::EIT_Backpack, Equipmentx->ID, "3DCharacter_Backpack");
			Attach(BackpackObj, PlayerControllerRef->BackpackName);

			
		}

	}
	if (HelmetObj) {
		SKM_Hair->SetVisibility(0, 0);
	}
	else {
		SKM_Hair->SetVisibility(1, 0);
	}



}

AItemBase* ACapture_Actor_Cpp::SpawnActorx(EItemType ItemType, FName ID, FName SN) {
	FTransform Transformx;
	Transformx.SetLocation(FVector::ZeroVector);
	AItemWeapon* ItemWpnToSpawn = nullptr;
	AItemWeaponAcc* ItemWpnAccToSpawn = nullptr;
	AItemEquipment* ItemEqToSpawn = nullptr;
	AItemFashion* ItemFToSpawn = nullptr;
	AItemBase* ItemCastToIB = nullptr;

	switch (ItemType) {
	case EItemType::EIT_Weapon:
		ItemWpnToSpawn = GetWorld()->SpawnActorDeferred<AItemWeapon>(AItemWeapon::StaticClass(), Transformx);
		if (ItemWpnToSpawn) {
			ItemWpnToSpawn->ID = ID;
			ItemWpnToSpawn->SN = SN;
			ItemWpnToSpawn->Amount = 1;
			ItemWpnToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemWpnToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}

		}


		break;
	case EItemType::EIT_Accessories:
		ItemWpnAccToSpawn = GetWorld()->SpawnActorDeferred<AItemWeaponAcc>(AItemWeaponAcc::StaticClass(), Transformx);
		if (ItemWpnAccToSpawn) {
			ItemWpnAccToSpawn->ID = ID;
			ItemWpnAccToSpawn->SN = SN;
			ItemWpnAccToSpawn->Amount = 1;
			ItemWpnAccToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemWpnAccToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}
		}

		break;
	case EItemType::EIT_Ammo:

		break;
	case EItemType::EIT_Health:

		break;
	case EItemType::EIT_Boost:


		break;
	case EItemType::EIT_Helmet:
		ItemEqToSpawn = GetWorld()->SpawnActorDeferred<AItemEquipment>(AItemEquipment::StaticClass(), Transformx);
		if (ItemEqToSpawn) {
			ItemEqToSpawn->ID = ID;
			ItemEqToSpawn->SN = SN;
			ItemEqToSpawn->Amount = 1;
			ItemEqToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemEqToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}
		}

		break;
	case EItemType::EIT_Vest:
		ItemEqToSpawn = GetWorld()->SpawnActorDeferred<AItemEquipment>(AItemEquipment::StaticClass(), Transformx);
		if (ItemEqToSpawn) {
			ItemEqToSpawn->ID = ID;
			ItemEqToSpawn->SN = SN;
			ItemEqToSpawn->Amount = 1;
			ItemEqToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemEqToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}
		}

		break;
	case EItemType::EIT_Backpack:
		ItemEqToSpawn = GetWorld()->SpawnActorDeferred<AItemEquipment>(AItemEquipment::StaticClass(), Transformx);
		if (ItemEqToSpawn) {
			ItemEqToSpawn->ID = ID;
			ItemEqToSpawn->SN = SN;
			ItemEqToSpawn->Amount = 1;
			ItemEqToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemEqToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}
		}

		break;
	case EItemType::EIT_Fashion:
		ItemFToSpawn = GetWorld()->SpawnActorDeferred<AItemFashion>(AItemFashion::StaticClass(), Transformx);
		if (ItemFToSpawn) {
			ItemFToSpawn->ID = ID;
			ItemFToSpawn->SN = SN;
			ItemFToSpawn->Amount = 1;
			ItemFToSpawn->FinishSpawning(Transformx);
			ItemCastToIB = Cast<AItemBase>(ItemFToSpawn);
			if (ItemCastToIB) {
				return ItemCastToIB;

			}
		}

		break;
	case EItemType::EIT_MAX:
		break;
	default:
		break;
	}








	


	return nullptr;
}

void ACapture_Actor_Cpp::Attach(AItemBase* Item, FName SocketName) {

	const USkeletalMeshSocket* GunSocket = SkeletalMesh->GetSocketByName(SocketName);
	const FTransform SocketTransform = GunSocket->GetSocketTransform(SkeletalMesh);
	Item->SetActorTransform(SocketTransform);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
	Item->AttachToComponent(SkeletalMesh, AttachmentRules, SocketName);




}

void ACapture_Actor_Cpp::ClearEquipments() {
	if (HelmetObj) {
		HelmetObj->Destroy();
		HelmetObj = nullptr;
	}
	if (VestObj) {
		VestObj->Destroy();
		VestObj = nullptr;
	}
	if (BackpackObj) {
		BackpackObj->Destroy();
		BackpackObj = nullptr;
	}



}


void ACapture_Actor_Cpp::InitSkeletalMesh() {
	SkinMatRef = SkeletalMesh->CreateAndSetMaterialInstanceDynamic(2);
	SKM_UnderwearTop->SetMasterPoseComponent(SkeletalMesh);
	SKM_UnderwearBottom->SetMasterPoseComponent(SkeletalMesh);
	SKM_ClothTop->SetMasterPoseComponent(SkeletalMesh);
	SKM_ClothBottom->SetMasterPoseComponent(SkeletalMesh);
	SKM_Whole->SetMasterPoseComponent(SkeletalMesh);
	SKM_Shoes->SetMasterPoseComponent(SkeletalMesh);


	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	SKM_Hair->AttachToComponent(SkeletalMesh, AttachmentRules, FName(TEXT("Head")));
	//SKM_Hair->SetRelativeLocation(FVector(132.538422f,20.360271f,99.221897f));
	//SKM_Hair->SetRelativeRotation(FRotator(219.589372f, 40.870872f, 239.76098f));
	ReplaceSkeletalMesh(EFashionType::EFT_ClothTop,"0");

}

USkeletalMesh* ACapture_Actor_Cpp::GetFashionDatas(FName ID) {
	FSTR_ItemFashion* ItemFashionRow = nullptr;
	USkeletalMesh* DataSkeletalMesh = nullptr;
	ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));
	if (ItemFashionRow) {
		DataSkeletalMesh = ItemFashionRow->SkeletalMesh;

	}

	return DataSkeletalMesh;


}

UTexture* ACapture_Actor_Cpp::GetFashionDatasTexture(FName ID) {
	FSTR_ItemFashion* ItemFashionRow = nullptr;
	UTexture* DataTexture = nullptr;
	ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));
	if (ItemFashionRow) {
		DataTexture = ItemFashionRow->MaskTexture;

	}

	return DataTexture;

}

void ACapture_Actor_Cpp::ReplaceSkeletalMesh(EFashionType FashionType, FName ID) {

	switch (FashionType) {
	case EFashionType::EFT_ClothTop:
		SKM_ClothTop->SetSkeletalMesh(GetFashionDatas(ID));
		if (GetFashionDatas(ID) != nullptr) {
			SKM_Whole->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef && GetFashionDatasTexture(ID)) {
			SkinMatRef->SetTextureParameterValue("Mask Top", GetFashionDatasTexture(ID));
		}

		break;
	case EFashionType::EFT_ClothBottom:
		SKM_ClothBottom->SetSkeletalMesh(GetFashionDatas(ID));
		if (GetFashionDatas(ID) != nullptr) {
			SKM_Whole->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef && GetFashionDatasTexture(ID)) {
			SkinMatRef->SetTextureParameterValue("Mask Bottom", GetFashionDatasTexture(ID));
		}

		break;
	case EFashionType::EFT_Whole:
		SKM_Whole->SetSkeletalMesh(GetFashionDatas(ID));
		if (GetFashionDatas(ID) != nullptr) {
			SKM_ClothTop->SetSkeletalMesh(nullptr);
			SKM_ClothBottom->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef && GetFashionDatasTexture(ID)) {
			SkinMatRef->SetTextureParameterValue("Mask Top", GetFashionDatasTexture(ID));
		}
		break;
	case EFashionType::EFT_Shoes:
		SKM_Shoes->SetSkeletalMesh(GetFashionDatas(ID));

		if (GetFashionDatas(ID)) {
			if (SkinMatRef && GetFashionDatasTexture(ID)) {
				SkinMatRef->SetTextureParameterValue("Mask Foot", GetFashionDatasTexture(ID));
			}
		}
		else {
			if (SkinMatRef && SkinMatTest) {
				SkinMatRef->SetTextureParameterValue("Mask Foot", SkinMatTest);
			}
		}


		break;
	case EFashionType::EFT_MAX:

		break;
	default:


		break;
	}

	if (SKM_Whole->SkeletalMesh != nullptr && SkinMatTest) {
		SkinMatRef->SetTextureParameterValue("Mask Bottom", SkinMatTest);
	}
	else {
		if (SKM_ClothTop->SkeletalMesh == nullptr && SkinMatTest) {

			SKM_ClothTop->SetSkeletalMesh(GetFashionDatas("1"));
			SkinMatRef->SetTextureParameterValue("Mask Top", GetFashionDatasTexture("1"));

		}
		if (SKM_ClothBottom->SkeletalMesh == nullptr && SkinMatTest) {

			SKM_ClothBottom->SetSkeletalMesh(GetFashionDatas("5"));
			SkinMatRef->SetTextureParameterValue("Mask Bottom", GetFashionDatasTexture("5"));

		}
	}



}

void ACapture_Actor_Cpp::UpdateFashionx(AItemBase* Fashion, bool bIsAdd) {

	if (!PlayerStateRef)return;
	ReplaceSkeletalMesh(EFashionType::EFT_ClothTop, "0");
	ReplaceSkeletalMesh(EFashionType::EFT_ClothBottom, "0");
	ReplaceSkeletalMesh(EFashionType::EFT_Whole, "0");
	ReplaceSkeletalMesh(EFashionType::EFT_Shoes, "0");
	


	AItemFashion* FashionCastToIF = nullptr;
	TArray<AItemBase*> Fashions = PlayerStateRef->GetFashions();
	for (AItemBase* Fashionx : Fashions) {
		FashionCastToIF = Cast<AItemFashion>(Fashionx);
		if (FashionCastToIF) {
			ReplaceSkeletalMesh(FashionCastToIF->FashionType,FashionCastToIF->ID);
		}

	}



}

void ACapture_Actor_Cpp::UpdateWeaponx(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand) {

	UpdateWeapon();

}

void ACapture_Actor_Cpp::UpdateWeapon() {

	if (!PlayerStateRef)return;
	if (!PlayerControllerRef)return;
	ClearWeapons();
	if (PlayerStateRef->GetHoldGun()) {
		HoldWeapon= SpawnActorx(EItemType::EIT_Weapon, PlayerStateRef->GetHoldGun()->ID,"3DCharacterWeaponHand");
		if (HoldWeapon) {
			Attach(HoldWeapon, PlayerControllerRef->GunStandName);
			UpdateAccessories(PlayerStateRef->GetHoldGun(),HoldWeapon);
		}
		

	}
	
	


	bool bIsEquipBackpack = 0;
	TArray<AItemBase*> Equipments = PlayerStateRef->GetEquipments();
	if (!Equipments.IsEmpty()) {
		for (AItemBase* Equipment : Equipments) {
			if (Equipment->ItemType == EItemType::EIT_Backpack) {
				bIsEquipBackpack = 1;

			}
		}

	}
	if (PlayerStateRef->GetWeapon1()) {
		LeftWeapon = SpawnActorx(EItemType::EIT_Weapon, PlayerStateRef->GetWeapon1()->ID, "3DCharacterWeapon_1");
		if (LeftWeapon) {
			UpdateAccessories(PlayerStateRef->GetWeapon1(), LeftWeapon);
			if (bIsEquipBackpack) {
				Attach(LeftWeapon, PlayerControllerRef->BackLeftBName);
			}
			else {
				Attach(LeftWeapon, PlayerControllerRef->BackLeftNName);
			}
		}
		

	}
	if (PlayerStateRef->GetWeapon2()) {
		RightWeapon= SpawnActorx(EItemType::EIT_Weapon, PlayerStateRef->GetWeapon2()->ID, "3DCharacterWeapon_2");
		if (RightWeapon) {
			UpdateAccessories(PlayerStateRef->GetWeapon2(), RightWeapon);

			if (bIsEquipBackpack) {
				Attach(RightWeapon, PlayerControllerRef->BackRightBName);
			}
			else {
				Attach(RightWeapon, PlayerControllerRef->BackRightNName);
			}
		}
		

	}


}

void ACapture_Actor_Cpp::ClearWeapons() {

	if (HoldWeapon) {
		HoldWeapon->Destroy();
		HoldWeapon = nullptr;
	}
	if (LeftWeapon) {
		LeftWeapon->Destroy();
		LeftWeapon = nullptr;
	}
	if (RightWeapon) {
		RightWeapon->Destroy();
		RightWeapon = nullptr;
	}

}

void ACapture_Actor_Cpp::UpdateAccessories(AItemBase* CharacterWeapon, AItemBase* d3DWeapon) {
	if (CharacterWeapon&& d3DWeapon) {
		AItemWeapon* d3DWeaponCastToIW = Cast<AItemWeapon>(d3DWeapon);
		AItemWeapon* CharWeaponCastToIW = Cast<AItemWeapon>(CharacterWeapon);

		if (d3DWeaponCastToIW && CharWeaponCastToIW) {
			d3DWeaponCastToIW->UpdateSight(CharWeaponCastToIW->AccSightObj);
			d3DWeaponCastToIW->UpdateButtstock(CharWeaponCastToIW->AccButtstockObj);
			d3DWeaponCastToIW->UpdateMuzzle(CharWeaponCastToIW->AccMuzzleObj);
			d3DWeaponCastToIW->UpdateMag(CharWeaponCastToIW->AccMagObj);
			d3DWeaponCastToIW->UpdateForegrip(CharWeaponCastToIW->AccForegripObj);
		}

	}

	


}

void ACapture_Actor_Cpp::UpdateWeaponAcc(AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType) {

	if (!PlayerStateRef)return;
	
	UpdateAccessories(PlayerStateRef->GetHoldGun(),HoldWeapon);
	UpdateAccessories(PlayerStateRef->GetWeapon1(), LeftWeapon);
	UpdateAccessories(PlayerStateRef->GetWeapon2(), RightWeapon);
}












