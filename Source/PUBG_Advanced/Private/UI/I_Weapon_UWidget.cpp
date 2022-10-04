// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/I_Weapon_UWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemWeapon.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "UI/I_Accessory_UWidget.h"



void UI_Weapon_UWidget::NativeConstruct() {

	Super::NativeConstruct();

	ItemAmmoTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ItemAmmo.DT_ItemAmmo'");
	ItemAmmoTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemAmmoTablePath));

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnWeaponChanged.AddDynamic(this, &UI_Weapon_UWidget::UpdateWeaponDisplay);
			UpdateWeaponDisplay(nullptr, EWeaponPosition::EWP_Left, 0);

			


		}

	}

}

void UI_Weapon_UWidget::NativeDestruct() {

	Super::NativeDestruct();
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnWeaponChanged.RemoveDynamic(this, &UI_Weapon_UWidget::UpdateWeaponDisplay);
		}


	}


}

void UI_Weapon_UWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {

	Super::NativeTick(MyGeometry,InDeltaTime);
	FString TempString = FString::FromInt(Locationx);
	FText TempText = FText::FromString(TempString);
	LocationID->SetText(TempText);


}

void UI_Weapon_UWidget::UpdateWeaponDisplay(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand) {
	if (!PlayerStateRef)return;
	ItemWeapon = nullptr;
	if (Locationx==1) {
		if (PlayerStateRef->GetWeapon1()) {
			ItemWeapon = PlayerStateRef->GetWeapon1();

		}
		else {
			if (PlayerStateRef->GetHoldGun()) {
				if (PlayerStateRef->GetHoldGun()->Position==EWeaponPosition::EWP_Left) {
					ItemWeapon = PlayerStateRef->GetHoldGun();
				}
			}
		}


	}
	else {
		if (PlayerStateRef->GetWeapon2()) {
			ItemWeapon = PlayerStateRef->GetWeapon2();

		}
		else {
			if (PlayerStateRef->GetHoldGun()) {
				if (PlayerStateRef->GetHoldGun()->Position == EWeaponPosition::EWP_Right) {
					ItemWeapon = PlayerStateRef->GetHoldGun();
				}
			}
		}

	}


	AccSight->SetOwner(ItemWeapon);
	AccSight->UpdateWeaponAccDisplay(nullptr, 0, nullptr, EWeaponAccType::EWAT_Sight);

	Acc_Muzzle->SetOwner(ItemWeapon);
	Acc_Muzzle->UpdateWeaponAccDisplay(nullptr, 0, nullptr, EWeaponAccType::EWAT_Muzzle);
	
	Acc_Mag->SetOwner(ItemWeapon);
	Acc_Mag->UpdateWeaponAccDisplay(nullptr, 0, nullptr, EWeaponAccType::EWAT_Mag);
	
	Acc_Foregrip->SetOwner(ItemWeapon);
	Acc_Foregrip->UpdateWeaponAccDisplay(nullptr, 0, nullptr, EWeaponAccType::EWAT_Foregrip);
	
	Acc_Buttstock->SetOwner(ItemWeapon);
	Acc_Buttstock->UpdateWeaponAccDisplay(nullptr, 0, nullptr, EWeaponAccType::EWAT_Buttstock);
	
	if (ItemWeapon) {
		if (ItemWeapon->Datas->bCanGrip) {
			Acc_Foregrip->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			Acc_Foregrip->SetVisibility(ESlateVisibility::Hidden);
		}
		if (ItemWeapon->Datas->bCanButtStock) {
			Acc_Buttstock->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			Acc_Buttstock->SetVisibility(ESlateVisibility::Hidden);
		}
	}


	if (ItemWeapon) {
		TopBox->SetVisibility(ESlateVisibility::Visible);
		WeaponImage->SetOpacity(1.f);
		AccCanvasPanel->SetVisibility(ESlateVisibility::Visible);

		NameText->SetText(FText::FromName(ItemWeapon->Datas->Name));
		WeaponImage->SetBrushFromTexture(ItemWeapon->Datas->Thumbnail);
		FSTR_ItemAmmo* ItemAmmoRow = nullptr;
		ItemAmmoRow = ItemAmmoTableObject->FindRow<FSTR_ItemAmmo>(ItemWeapon->Datas->UseAmmoID, TEXT(""));
		if (ItemAmmoRow) {
			BulletTypeText->SetText(FText::FromName(ItemAmmoRow->Name));
		}
		FString TempString = FString::FromInt(ItemWeapon->Ammo);
		FText TempText = FText::FromString(TempString);
		ClipAmountText->SetText(TempText);
		if (ItemWeapon->Datas->UseAmmoID=="1") {
			FString TempString1 = FString::FromInt(PlayerStateRef->GetAmmo556());
			FText TempText1 = FText::FromString(TempString1);
			RemainingAmountText->SetText(TempText1);
		}
		else if (ItemWeapon->Datas->UseAmmoID == "2") {
			FString TempString2 = FString::FromInt(PlayerStateRef->GetAmmo762());
			FText TempText2 = FText::FromString(TempString2);
			RemainingAmountText->SetText(TempText2);
		}



	}
	else {
		TopBox->SetVisibility(ESlateVisibility::Hidden);
		WeaponImage->SetOpacity(0.f);
		AccCanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	}




}
