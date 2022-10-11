// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PUBGA_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<UUserWidget> ActionTipsWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<UUserWidget> UserInfoWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<UUserWidget> DirectionUIWidgetClass;

	virtual void BeginPlay() override;

	UUserWidget* ActionTipsHUDWidget;

	UUserWidget* UserInfoHUDWidget;

	UUserWidget* DirectionUIHUDWidget;

public:
	void ShowActionTips(FName Info);

	void HideActionTips();




};
