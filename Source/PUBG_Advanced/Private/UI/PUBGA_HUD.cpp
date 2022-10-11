// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/PUBGA_HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "UI/MainUI/ActionTips_UWidget.h"


void APUBGA_HUD::BeginPlay() {

	Super::BeginPlay();
	
	UUserWidget* PlayerHUDWidget = nullptr;

	if(PlayerHUDWidgetClass)
	PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget) {
		PlayerHUDWidget->AddToViewport();
	}

	if(ActionTipsWidgetClass)
	ActionTipsHUDWidget = CreateWidget<UUserWidget>(GetWorld(), ActionTipsWidgetClass);
	if (ActionTipsHUDWidget) {
		ActionTipsHUDWidget->SetVisibility(ESlateVisibility::Hidden);
		ActionTipsHUDWidget->AddToViewport();
	}


	if (UserInfoWidgetClass)
		UserInfoHUDWidget = CreateWidget<UUserWidget>(GetWorld(), UserInfoWidgetClass);
	if (UserInfoHUDWidget) {
		
		UserInfoHUDWidget->AddToViewport();
	}

	if (DirectionUIWidgetClass)
		DirectionUIHUDWidget = CreateWidget<UUserWidget>(GetWorld(), DirectionUIWidgetClass);
	if (DirectionUIHUDWidget) {

		DirectionUIHUDWidget->AddToViewport();
	}




}

void APUBGA_HUD::ShowActionTips(FName Info) {
	if (ActionTipsHUDWidget) {
		UActionTips_UWidget* ActionTipsHUDWidgetTemp = Cast<UActionTips_UWidget>(ActionTipsHUDWidget);
		if (ActionTipsHUDWidgetTemp) {
			ActionTipsHUDWidgetTemp->SetInfo(Info);
			ActionTipsHUDWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	


}

void APUBGA_HUD::HideActionTips() {
	if (ActionTipsHUDWidget) {
	
		ActionTipsHUDWidget->SetVisibility(ESlateVisibility::Hidden);

	}


}
