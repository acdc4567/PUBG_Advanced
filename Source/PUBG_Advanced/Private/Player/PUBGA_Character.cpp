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



// Sets default values
APUBGA_Character::APUBGA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);

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


	

}

// Called when the game starts or when spawned
void APUBGA_Character::BeginPlay()
{
	Super::BeginPlay();
	

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
		MyPlayerControllerRef = SPC;
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







