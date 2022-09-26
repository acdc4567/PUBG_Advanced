// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Player/PUBGA_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PUBGA_Structs.h"
#include "Engine/Texture.h"
#include "Items/PickUpBase.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Items/ItemWeapon.h"
#include "Items/ItemFashion.h"
#include "Animation/Notifies/OnEquipAnimNotify.h"
#include "Animation/Notifies/OnEquipEndAnimNotify.h"
#include "Animation/Notifies/OnUnEquipAnimNotify.h"
#include "Animation/Notifies/OnUnEquipEndAnimNotify.h"
#include "Animation/Notifies/FireEndAnimNotify.h"
#include "Animation/Notifies/ReloadEndAnimNotify.h"
#include "Items/ItemWeaponAcc.h"



// Sets default values
APUBGA_Character::APUBGA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);

	FPS_Camera = CreateDefaultSubobject<UCameraComponent>("FPS_Camera");
	FPS_Camera->AddRelativeLocation(FVector(0.f,0.f,75.f));
	FPS_Camera->bUsePawnControlRotation = 1;
	FPS_Camera->SetupAttachment(GetRootComponent());

	FPS_Arms = CreateDefaultSubobject<USkeletalMeshComponent>("FPS_Arms");
	FPS_Arms->SetupAttachment(FPS_Camera);

	GetCharacterMovement()->bUseSeparateBrakingFriction = 1;

	SKM_Hair = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Hair");
	//SKM_Hair->AddRelativeLocation(FVector(1.f, 1.f, 1.f));
	SKM_Hair->SetupAttachment(GetMesh());
	
	SKM_UnderwearTop = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_UnderwearTop");
	SKM_UnderwearTop->SetupAttachment(GetMesh());

	SKM_UnderwearBottom = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_UnderwearBottom");
	SKM_UnderwearBottom->SetupAttachment(GetMesh());

	SKM_ClothTop = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_ClothTop");
	SKM_ClothTop->SetupAttachment(GetMesh());

	SKM_ClothBottom = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_ClothBottom");
	SKM_ClothBottom->SetupAttachment(GetMesh());

	SKM_Whole = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Whole");
	SKM_Whole->SetupAttachment(GetMesh());

	SKM_Shoes = CreateDefaultSubobject<USkeletalMeshComponent>("SKM_Shoes");
	SKM_Shoes->SetupAttachment(GetMesh());

	ItemFashionTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemFashion.DT_ItemFashion'");
	ItemFashionTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemFashionTablePath));

	ArmsLocationTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ArmsLocation.DT_ArmsLocation'");
	ArmsLocationTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ArmsLocationTablePath));

	

}

// Called when the game starts or when spawned
void APUBGA_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (Controller != nullptr) {
		PlayerStateRef = Cast<APUBGA_PlayerState>(Controller->PlayerState);

	}

	InitAnimations();


}


void APUBGA_Character::MouseTurn(float AxisValue) {

	AddControllerYawInput(AxisValue*.5f);

}

void APUBGA_Character::MouseLookUp(float AxisValue) {

	AddControllerPitchInput(AxisValue*.5f);

}


// Called every frame
void APUBGA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APUBGA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APUBGA_Character::PossessedBy(AController* inController) {

	APUBGA_PlayerController* SPC = Cast<APUBGA_PlayerController>(inController);
	if (SPC) {
		PlayerControllerRef = SPC;
		SPC->OnPossessx1(this);

	}
}

void APUBGA_Character::SetIsProne(const bool& Value) {
	bIsProne = Value;
}

void APUBGA_Character::SetIsCrouching(const bool& Value){
	bIsCrouching = Value;
}
void APUBGA_Character::SetIsAiming(const bool& Value){
	bIsAiming = Value;
}

void APUBGA_Character::InitSkeletalMesh() {
	SkinMatRef = GetMesh()->CreateAndSetMaterialInstanceDynamic(2);
	SKM_UnderwearTop->SetMasterPoseComponent(GetMesh());
	SKM_UnderwearBottom->SetMasterPoseComponent(GetMesh());
	SKM_ClothTop->SetMasterPoseComponent(GetMesh());
	SKM_ClothBottom->SetMasterPoseComponent(GetMesh());
	SKM_Whole->SetMasterPoseComponent(GetMesh());
	SKM_Shoes->SetMasterPoseComponent(GetMesh());


	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	SKM_Hair->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("Head")));

	ReplaceSkeletalMesh(EFashionType::EFT_ClothBottom,"0");

}

void APUBGA_Character::ReplaceSkeletalMesh(EFashionType FashionType, FName Namex) {
	
	switch (FashionType) {
	case EFashionType::EFT_ClothTop:
		SKM_ClothTop->SetSkeletalMesh(GetFashionDatas(Namex));
		if (GetFashionDatas(Namex)!=nullptr) {
			SKM_Whole->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef &&GetFashionDatasTexture(Namex)) {
			SkinMatRef->SetTextureParameterValue("Mask Top", GetFashionDatasTexture(Namex));
		}
		
		break;
	case EFashionType::EFT_ClothBottom:
		SKM_ClothBottom->SetSkeletalMesh(GetFashionDatas(Namex));
		if (GetFashionDatas(Namex) != nullptr) {
			SKM_Whole->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef && GetFashionDatasTexture(Namex)) {
			SkinMatRef->SetTextureParameterValue("Mask Bottom", GetFashionDatasTexture(Namex));
		}

		break;
	case EFashionType::EFT_Whole:
		SKM_Whole->SetSkeletalMesh(GetFashionDatas(Namex));
		if (GetFashionDatas(Namex) != nullptr) {
			SKM_ClothTop->SetSkeletalMesh(nullptr);
			SKM_ClothBottom->SetSkeletalMesh(nullptr);
		}
		if (SkinMatRef && GetFashionDatasTexture(Namex)) {
			SkinMatRef->SetTextureParameterValue("Mask Top", GetFashionDatasTexture(Namex));
		}
		break;
	case EFashionType::EFT_Shoes:
		SKM_Shoes->SetSkeletalMesh(GetFashionDatas(Namex));
		
		if (GetFashionDatas(Namex)) {
			if (SkinMatRef && GetFashionDatasTexture(Namex)) {
				SkinMatRef->SetTextureParameterValue("Mask Foot", GetFashionDatasTexture(Namex));
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

	if (SKM_Whole->SkeletalMesh!=nullptr&&SkinMatTest) {
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

USkeletalMesh* APUBGA_Character::GetFashionDatas(FName ID) {
	FSTR_ItemFashion* ItemFashionRow = nullptr;
	USkeletalMesh* DataSkeletalMesh=nullptr;
	ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));
	if (ItemFashionRow) {
		DataSkeletalMesh = ItemFashionRow->SkeletalMesh;
		
	}
	
	return DataSkeletalMesh;


}



UTexture* APUBGA_Character::GetFashionDatasTexture(FName ID) {
	FSTR_ItemFashion* ItemFashionRow = nullptr;
	UTexture* DataTexture = nullptr;
	ItemFashionRow = ItemFashionTableObject->FindRow<FSTR_ItemFashion>(ID, TEXT(""));
	if (ItemFashionRow) {
		DataTexture = ItemFashionRow->MaskTexture;

	}

	return DataTexture;

}


void APUBGA_Character::UpdateWeaponDisplay(FName HoldSocket) {
	if (!PlayerStateRef)return;
	if (!PlayerControllerRef)return;
	if (!bIsSightAiming) {
		if (HoldSocket != "None") {
			if (PlayerStateRef->GetHoldGun()) {
				Attach(PlayerStateRef->GetHoldGun(), HoldSocket);

			}
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
		if (bIsEquipBackpack) {
			Attach(PlayerStateRef->GetWeapon1(), PlayerControllerRef->BackLeftBName);
		}
		else {
			Attach(PlayerStateRef->GetWeapon1(), PlayerControllerRef->BackLeftNName);
		}

	}
	if (PlayerStateRef->GetWeapon2()) {
		if (bIsEquipBackpack) {
			Attach(PlayerStateRef->GetWeapon2(), PlayerControllerRef->BackRightBName);
		}
		else {
			Attach(PlayerStateRef->GetWeapon2(), PlayerControllerRef->BackRightNName);
		}

	}






}

void APUBGA_Character::Attach(AItemWeapon* WeaponToAttach, FName SocksName) {
	
	const USkeletalMeshSocket* GunSocket = GetMesh()->GetSocketByName(SocksName);
	const FTransform SocketTransform = GunSocket->GetSocketTransform(GetMesh());
	WeaponToAttach->SetActorTransform(SocketTransform);
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
	WeaponToAttach->AttachToComponent(GetMesh(), AttachmentRules, SocksName);

}

void APUBGA_Character::UpdateEquipmentDisplay() {
	if (!PlayerStateRef)return;
	if (!PlayerControllerRef)return;

	bool bHasHelmet = 0;

	TArray<AItemBase*> Equipments = PlayerStateRef->GetEquipments();
	if (!Equipments.IsEmpty()) {

		for (AItemBase* Equipment : Equipments) {
			if (Equipment->ItemType == EItemType::EIT_Helmet) {
				const USkeletalMeshSocket* HelmetSocket = GetMesh()->GetSocketByName(PlayerControllerRef->HelmetName);
				const FTransform SocketTransform = HelmetSocket->GetSocketTransform(GetMesh());
				Equipment->SetActorTransform(SocketTransform);
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
				Equipment->AttachToComponent(GetMesh(), AttachmentRules, PlayerControllerRef->HelmetName);

				bHasHelmet = 1;

			}
			else if(Equipment->ItemType == EItemType::EIT_Vest) {
				const USkeletalMeshSocket* VestSocket = GetMesh()->GetSocketByName(PlayerControllerRef->VestName);
				const FTransform SocketTransform1 = VestSocket->GetSocketTransform(GetMesh());
				Equipment->SetActorTransform(SocketTransform1);
				FAttachmentTransformRules AttachmentRules1(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
				Equipment->AttachToComponent(GetMesh(), AttachmentRules1, PlayerControllerRef->VestName);

			}
			else if(Equipment->ItemType == EItemType::EIT_Backpack) {
				const USkeletalMeshSocket* BPSocket = GetMesh()->GetSocketByName(PlayerControllerRef->BackpackName);
				const FTransform SocketTransform2 = BPSocket->GetSocketTransform(GetMesh());
				Equipment->SetActorTransform(SocketTransform2);
				FAttachmentTransformRules AttachmentRules2(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
				Equipment->AttachToComponent(GetMesh(), AttachmentRules2, PlayerControllerRef->BackpackName);

			}

			

		}

	}
	if (bHasHelmet) {
		SKM_Hair->SetVisibility(0,0);
	}
	else {
		SKM_Hair->SetVisibility(1, 0);
	}





}

void APUBGA_Character::ClearFashion() {
	ReplaceSkeletalMesh(EFashionType::EFT_ClothTop,"0");
	ReplaceSkeletalMesh(EFashionType::EFT_ClothBottom, "0");
	ReplaceSkeletalMesh(EFashionType::EFT_Whole, "0");
	ReplaceSkeletalMesh(EFashionType::EFT_Shoes, "0");


}

void APUBGA_Character::UpdateFashionDisplay() {
	if (!PlayerStateRef)return;
	
	ClearFashion();
	TArray<AItemBase*> Fashions = PlayerStateRef->GetFashions();
	if (!Fashions.IsEmpty()) {
		for (AItemBase* Fashion : Fashions) {
			AItemFashion* TempFashion = Cast<AItemFashion>(Fashion);
			if (TempFashion) {
				ReplaceSkeletalMesh(TempFashion->FashionType,TempFashion->ID);
			}

		}


	}

}



void APUBGA_Character::PlayMontage(EMontageType MontageType, float InPlayRates) {
	PlayingMontageType = MontageType;
	bIsPlayingMontage = 1;
	if (bIsProne) {

		switch (MontageType) {
		case EMontageType::EMT_Equip:
			PlayAnimMontage(ProneEquipMontage);

			break;
		case EMontageType::EMT_UnEquip:
			PlayAnimMontage(ProneUnEquipMontage);

			break;
		case EMontageType::EMT_Reload:
			PlayAnimMontage(ProneReloadMontage,InPlayRates);

			break;
		case EMontageType::EMT_ReloadBullet:
			PlayAnimMontage(ProneReloadMontage,1.f,"ReloadBullet");

			break;
		case EMontageType::EMT_Fire:
			PlayAnimMontage(ProneFireMontage,.466f);

			break;
		case EMontageType::EMT_UseItem:
			PlayAnimMontage(ProneUseMontage);

			break;
		case EMontageType::EMT_MAX:
			PlayAnimMontage(ProneUseMontage);

			break;
		default:
			break;
		}
	}
	else {
		if (bIsCrouching) {

			switch (MontageType) {
			case EMontageType::EMT_Equip:
				PlayAnimMontage(CrouchEquipMontage);

				break;
			case EMontageType::EMT_UnEquip:
				PlayAnimMontage(CrouchUnEquipMontage);

				break;
			case EMontageType::EMT_Reload:
				PlayAnimMontage(CrouchReloadMontage,InPlayRates);

				break;
			case EMontageType::EMT_ReloadBullet:
				PlayAnimMontage(CrouchReloadMontage, 1.f, "ReloadBullet");

				break;
			case EMontageType::EMT_Fire:
				PlayAnimMontage(CrouchFireMontage,2.f);

				break;
			case EMontageType::EMT_UseItem:
				PlayAnimMontage(CrouchUseMontage);

				break;
			case EMontageType::EMT_MAX:
				PlayAnimMontage(CrouchUseMontage);

				break;
			default:
				break;
			}


		}
		else {
			switch (MontageType) {
			case EMontageType::EMT_Equip:
				PlayAnimMontage(StandEquipMontage);

				break;
			case EMontageType::EMT_UnEquip:
				PlayAnimMontage(StandUnEquipMontage);

				break;
			case EMontageType::EMT_Reload:
				PlayAnimMontage(StandReloadMontage,InPlayRates);

				break;
			case EMontageType::EMT_ReloadBullet:
				PlayAnimMontage(StandReloadMontage, 1.f, "ReloadBullet");

				break;
			case EMontageType::EMT_Fire:
				PlayAnimMontage(StandFireMontage,2.f);

				break;
			case EMontageType::EMT_UseItem:
				PlayAnimMontage(StandUseMontage);

				break;
			case EMontageType::EMT_MAX:
				PlayAnimMontage(StandUseMontage);

				break;
			default:
				break;
			}
		}
	}



}


void APUBGA_Character::InitAnimations() {
	

	if (!StandEquipMontage)return;
	if (!StandUnEquipMontage)return;
	if (!StandReloadMontage)return;
	if (!StandFireMontage)return;
	if (!StandUseMontage)return;
	if (!CrouchEquipMontage)return;
	if (!CrouchUnEquipMontage)return;
	if (!CrouchReloadMontage)return;
	if (!CrouchFireMontage)return;
	if (!CrouchUseMontage)return;
	if (!ProneEquipMontage)return;
	if (!ProneUnEquipMontage)return;
	if (!ProneReloadMontage)return;
	if (!ProneFireMontage)return;
	if (!ProneUseMontage)return;
	if (!ArmsFireMontage)return;


	const auto NotifyEvents = StandEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents) {
		auto EquipNotify = Cast<UOnEquipAnimNotify>(NotifyEvent.Notify);
		if (EquipNotify) {
			EquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::EquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents) {
		auto EquipEndNotify = Cast<UOnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (EquipEndNotify) {
			EquipEndNotify->OnNotifiedEnd.AddUObject(this, &APUBGA_Character::EquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents1 = StandUnEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents1) {
		auto UnEquipNotify = Cast<UOnUnEquipAnimNotify>(NotifyEvent.Notify);
		if (UnEquipNotify) {
			UnEquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents1) {
		auto UnEquipEndNotify = Cast<UOnUnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (UnEquipEndNotify) {
			UnEquipEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents2 = StandReloadMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents2) {
		auto ReloadNotify = Cast<UReloadEndAnimNotify>(NotifyEvent.Notify);
		if (ReloadNotify) {
			ReloadNotify->OnNotified.AddUObject(this, &APUBGA_Character::ReloadEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents3 = StandFireMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents3) {
		auto FireEndNotify = Cast<UFireEndAnimNotify>(NotifyEvent.Notify);
		if (FireEndNotify) {
			FireEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::FireEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents4 = CrouchEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents4) {
		auto EquipNotify = Cast<UOnEquipAnimNotify>(NotifyEvent.Notify);
		if (EquipNotify) {
			EquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::EquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents4) {
		auto EquipEndNotify = Cast<UOnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (EquipEndNotify) {
			EquipEndNotify->OnNotifiedEnd.AddUObject(this, &APUBGA_Character::EquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents5 = CrouchUnEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents5) {
		auto UnEquipNotify = Cast<UOnUnEquipAnimNotify>(NotifyEvent.Notify);
		if (UnEquipNotify) {
			UnEquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents5) {
		auto UnEquipEndNotify = Cast<UOnUnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (UnEquipEndNotify) {
			UnEquipEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents6 = CrouchReloadMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents6) {
		auto ReloadNotify = Cast<UReloadEndAnimNotify>(NotifyEvent.Notify);
		if (ReloadNotify) {
			ReloadNotify->OnNotified.AddUObject(this, &APUBGA_Character::ReloadEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents7 = CrouchFireMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents7) {
		auto FireEndNotify = Cast<UFireEndAnimNotify>(NotifyEvent.Notify);
		if (FireEndNotify) {
			FireEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::FireEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents8 = ProneEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents8) {
		auto EquipNotify = Cast<UOnEquipAnimNotify>(NotifyEvent.Notify);
		if (EquipNotify) {
			EquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::EquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents8) {
		auto EquipEndNotify = Cast<UOnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (EquipEndNotify) {
			EquipEndNotify->OnNotifiedEnd.AddUObject(this, &APUBGA_Character::EquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents9 = ProneUnEquipMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents9) {
		auto UnEquipNotify = Cast<UOnUnEquipAnimNotify>(NotifyEvent.Notify);
		if (UnEquipNotify) {
			UnEquipNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipNotifyHandle);

			break;
		}

	}
	for (auto NotifyEvent : NotifyEvents9) {
		auto UnEquipEndNotify = Cast<UOnUnEquipEndAnimNotify>(NotifyEvent.Notify);
		if (UnEquipEndNotify) {
			UnEquipEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::UnEquipFinishedNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents10 = ProneReloadMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents10) {
		auto ReloadNotify = Cast<UReloadEndAnimNotify>(NotifyEvent.Notify);
		if (ReloadNotify) {
			ReloadNotify->OnNotified.AddUObject(this, &APUBGA_Character::ReloadEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents11 = ProneFireMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents11) {
		auto FireEndNotify = Cast<UFireEndAnimNotify>(NotifyEvent.Notify);
		if (FireEndNotify) {
			FireEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::FireEndNotifyHandle);

			break;
		}

	}

	const auto NotifyEvents12 = ArmsFireMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents12) {
		auto FireEndNotify = Cast<UFireEndAnimNotify>(NotifyEvent.Notify);
		if (FireEndNotify) {
			FireEndNotify->OnNotified.AddUObject(this, &APUBGA_Character::FireEndNotifyHandle);

			break;
		}

	}


}


void APUBGA_Character::EquipNotifyHandle(USkeletalMeshComponent* MyMesh) {
	if (!PlayerControllerRef)return;
	PlayerControllerRef->EquipWeapon();

}

void APUBGA_Character::EquipFinishedNotifyHandle(USkeletalMeshComponent* MyMesh) {

}

void APUBGA_Character::UnEquipNotifyHandle(USkeletalMeshComponent* MyMesh){
	if (!PlayerControllerRef)return;
	PlayerControllerRef->TakeBackWeapon();

}

void APUBGA_Character::UnEquipFinishedNotifyHandle(USkeletalMeshComponent* MyMesh){


}

void APUBGA_Character::FireEndNotifyHandle(USkeletalMeshComponent* MyMesh) {

	if (!PlayerStateRef)return;

	if (PlayerStateRef->GetHoldGun()->Ammo == 0) {
		PlayerControllerRef->ExecuteReload();
	}



}

void APUBGA_Character::ReloadEndNotifyHandle(USkeletalMeshComponent* MyMesh) {
	if (!PlayerControllerRef)return;
	PlayerControllerRef->Event_ReloadEnd();
}


void APUBGA_Character::ReturnedCameraLocation(FVector RetVec) {
	FollowCamera->SetRelativeLocation(RetVec);

}

void APUBGA_Character::SwitchCamera(bool bIsFirst) {
	if (!PlayerStateRef)return;
	if (!PlayerControllerRef)return;
	FPS_Arms->SetVisibility(bIsFirst, 1);
	FPS_Camera->SetActive(bIsFirst, 0);
	GetMesh()->SetVisibility(!bIsFirst, 1);
	FollowCamera->SetActive(!bIsFirst, 0);


	FTransform NewTransfrm;
	if (bIsFirst) {
		NewTransfrm = FPS_Arms->GetSocketTransform(FName("WeaponSocket"));
	}
	else {
		FName TPS_SocketTransformName = PlayerControllerRef->CalculateHoldGunSocket();
		NewTransfrm = GetMesh()->GetSocketTransform(TPS_SocketTransformName);
	}
	PlayerStateRef->GetHoldGun()->SetActorTransform(NewTransfrm);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true);
	if (bIsFirst) {
		PlayerStateRef->GetHoldGun()->AttachToComponent(FPS_Arms, AttachmentRules, FName("WeaponSocket"));
	}
	else {
		PlayerStateRef->GetHoldGun()->AttachToComponent(GetMesh(), AttachmentRules, PlayerControllerRef->CalculateHoldGunSocket());
	}

	PlayerStateRef->GetHoldGun()->SkeletalMesh->SetVisibility(1, 1);

	if (PlayerStateRef->GetHoldGun()->AccSightObj) {
		if (PlayerStateRef->GetHoldGun()->AccSightObj->ID == "2"&&bIsFirst) {
			PlayerStateRef->GetHoldGun()->Sight->SetRelativeScale3D(FVector(.1f, 1.f, 1.f));

			FPS_Camera->SetFieldOfView(28.f);
			FPS_Arms->SetVisibility(0, 0);
		}
		else {
			PlayerStateRef->GetHoldGun()->Sight->SetRelativeScale3D(FVector(1.f));
			FPS_Camera->SetFieldOfView(90.f);
		}
	}
	FName WeaponID;
	FName SightID;
	if (bIsFirst) {
		WeaponID = PlayerStateRef->GetHoldGun()->ID;
		if (PlayerStateRef->GetHoldGun()->AccSightObj) {
			SightID = PlayerStateRef->GetHoldGun()->AccSightObj->ID;
		}
		else {
			SightID = "0";
		}


		FSTR_ArmsLocation* ArmsLocationRow = nullptr;
		if (WeaponID == "1" && SightID == "0") {
			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("1_0", TEXT(""));
		}
		else if (WeaponID == "2" && SightID == "0") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("2_0", TEXT(""));
		}
		else if (WeaponID == "3" && SightID == "0") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("3_0", TEXT(""));
		}
		else if (WeaponID == "1" && SightID == "1") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("1_1", TEXT(""));
		}
		else if (WeaponID == "2" && SightID == "1") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("2_1", TEXT(""));
		}
		else if (WeaponID == "3" && SightID == "1") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("3_1", TEXT(""));
		}
		else if (WeaponID == "1" && SightID == "2") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("1_2", TEXT(""));
		}
		else if (WeaponID == "2" && SightID == "2") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("2_2", TEXT(""));
		}
		else if (WeaponID == "3" && SightID == "2") {

			ArmsLocationRow = ArmsLocationTableObject->FindRow<FSTR_ArmsLocation>("3_2", TEXT(""));
		}
		if (ArmsLocationRow) {
			FPS_Arms->SetRelativeLocation(ArmsLocationRow->Location);
		}

	}
	
	TArray<AItemBase*> EquippedItems = PlayerStateRef->GetEquipments();
	for (AItemBase* EquippedItem: EquippedItems) {
		if (EquippedItem->ItemType == EItemType::EIT_Helmet && !bIsFirst) {
			SKM_Hair->SetVisibility(0, 1);
		}
	}







}






