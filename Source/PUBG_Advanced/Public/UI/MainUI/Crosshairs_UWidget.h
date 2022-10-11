// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"
#include "Crosshairs_UWidget.generated.h"


class APUBGA_PlayerController;
class UImage;
class APUBGA_PlayerState;
class APUBGA_Character;



/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UCrosshairs_UWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:


	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_Character* PlayerCharacterRef;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageCenter;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageBottom;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageRight;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageLeft;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageTop;

	void UpdateCross(float LeftX, float RightX, float TopY, float DownY, float DeltaTime, float CLeftX = 0.f, float CRightX = 0.f, float CTopY = 0.f, float CDownY = 0.f);













};
