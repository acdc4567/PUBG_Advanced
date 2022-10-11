// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/MainUI/Crosshairs_UWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Player/PUBGA_Character.h"
#include "Components/Image.h"
#include "Items/ItemWeapon.h"



void UCrosshairs_UWidget::NativeConstruct() {
	Super::NativeConstruct();


	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerCharacterRef = Cast<APUBGA_Character>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			

		}

	}


}

void UCrosshairs_UWidget::NativeDestruct() {



}

void UCrosshairs_UWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {

	Super::NativeTick(MyGeometry, InDeltaTime);
	if (!PlayerControllerRef)return;
	if (!PlayerCharacterRef)return;
	if (!PlayerStateRef)return;

	if (PlayerCharacterRef->GetIsUmbrellaOpen()||PlayerCharacterRef->GetIsFreeFalling()||PlayerControllerRef->GetIsRunPressed()) {
		//ImageCenter->SetVisibility(ESlateVisibility::Hidden);
		ImageBottom->SetVisibility(ESlateVisibility::Hidden);
		ImageRight->SetVisibility(ESlateVisibility::Hidden);
		ImageLeft->SetVisibility(ESlateVisibility::Hidden);
		ImageTop->SetVisibility(ESlateVisibility::Hidden);


	}
	else {
		ImageCenter->SetVisibility(ESlateVisibility::Visible);
		if (PlayerCharacterRef->GetIsHoldWeapon()) {

			ImageBottom->SetVisibility(ESlateVisibility::Visible);
			ImageRight->SetVisibility(ESlateVisibility::Visible);
			ImageLeft->SetVisibility(ESlateVisibility::Visible);
			ImageTop->SetVisibility(ESlateVisibility::Visible);

			if (PlayerCharacterRef->GetIsSightAiming()) {
				ImageCenter->SetVisibility(ESlateVisibility::Hidden);
				ImageBottom->SetVisibility(ESlateVisibility::Hidden);
				ImageRight->SetVisibility(ESlateVisibility::Hidden);
				ImageLeft->SetVisibility(ESlateVisibility::Hidden);
				ImageTop->SetVisibility(ESlateVisibility::Hidden);
			}
			else {
				ImageCenter->SetVisibility(ESlateVisibility::Visible);
				ImageBottom->SetVisibility(ESlateVisibility::Visible);
				ImageRight->SetVisibility(ESlateVisibility::Visible);
				ImageLeft->SetVisibility(ESlateVisibility::Visible);
				ImageTop->SetVisibility(ESlateVisibility::Visible);
			}


		}
		else {
			
			ImageBottom->SetVisibility(ESlateVisibility::Hidden);
			ImageRight->SetVisibility(ESlateVisibility::Hidden);
			ImageLeft->SetVisibility(ESlateVisibility::Hidden);
			ImageTop->SetVisibility(ESlateVisibility::Hidden);
		}



	}

	if (PlayerStateRef->GetHoldGun()) {
		if (PlayerControllerRef->GetMoveForwardAxis() == 0.f && PlayerControllerRef->GetMoveRightAxis() == 0.f) {

			if (PlayerCharacterRef->GetIsAiming()) {
				float CrossOffAimStillMin = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Min_AimStillness;
				float CrossOffAimStillMax = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Max_AimStillness;
				
				
				UpdateCross(CrossOffAimStillMin, CrossOffAimStillMax, CrossOffAimStillMin, CrossOffAimStillMax, InDeltaTime);



			}
			else {
				float CrossOffStillMin = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Min_Stillness;
				float CrossOffStillMax = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Max_Stillness;
				UpdateCross(CrossOffStillMin, CrossOffStillMax, CrossOffStillMin, CrossOffStillMax,  InDeltaTime);


			}

		}
		else {

			if (PlayerCharacterRef->GetIsAiming()) {
				float CrossOffAimMoveMin = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Min_AimMove * .5f;
				float CrossOffAimMoveMax = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Max_AimMove * .5f;
				UpdateCross(CrossOffAimMoveMin, CrossOffAimMoveMax, CrossOffAimMoveMin, CrossOffAimMoveMax,  InDeltaTime);



			}
			else {
				float CrossOffMoveMin = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Min_Move * .5f;
				float CrossOffMoveMax = PlayerStateRef->GetHoldGun()->Datas->CrossOffset_Max_Move * .5f;
				UpdateCross(CrossOffMoveMin, CrossOffMoveMax, CrossOffMoveMin, CrossOffMoveMax,  InDeltaTime);


			}
		}




	}





}

void UCrosshairs_UWidget::UpdateCross(float LeftX, float RightX, float TopY, float DownY, float DeltaTime, float CLeftX , float CRightX , float CTopY , float CDownY ) {
	
	
	ImageLeft->SetRenderTranslation(FVector2D(LeftX * .5f, 0));
	ImageRight->SetRenderTranslation(FVector2D(RightX * .5f, 0));
	ImageTop->SetRenderTranslation(FVector2D(0, TopY * .5f));
	ImageBottom->SetRenderTranslation(FVector2D(0, DownY * .5f));
	
}
