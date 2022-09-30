// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/PUBGA_HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"


void APUBGA_HUD::BeginPlay() {

	Super::BeginPlay();

	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget) {
		PlayerHUDWidget->AddToViewport();
	}



}
