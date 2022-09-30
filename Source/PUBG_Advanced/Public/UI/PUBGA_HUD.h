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

	virtual void BeginPlay() override;



};
