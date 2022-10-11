// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "Styling/SlateBrush.h"
#include "Direction_UWidget.generated.h"


class UImage;
class APUBGA_PlayerController;
class APUBGA_PlayerState;
class UCanvasPanelSlot;
class UTextBlock;



/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UDirection_UWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
		UImage* WorldImage;

	UCanvasPanelSlot* WorldImageSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	float XToOneDegree = 0.f;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentDirection;

};
