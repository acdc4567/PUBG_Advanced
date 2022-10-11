// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/MainUI/Direction_UWidget.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextBlock.h"




void UDirection_UWidget::NativeConstruct() {
	Super::NativeConstruct();

	WorldImageSlot = Cast<UCanvasPanelSlot>(WorldImage->Slot);

	FSlateBrush* WorldImageSlateBrush = &WorldImage->Brush;

	XToOneDegree = WorldImageSlateBrush->ImageSize.X / 360.f;

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	



}

void UDirection_UWidget::NativeDestruct() {
	Super::NativeDestruct();




}

void UDirection_UWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	FRotator ControlRot;
	if (PlayerControllerRef) {
		ControlRot = PlayerControllerRef->GetControlRotation();
	}
	FRotator Delta2Rot = FRotator(270.f, 270.f, 270.f);

	float MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, Delta2Rot).Yaw;

	

	FVector2D WorldImageSlotPos = FVector2D(MovementOffsetYaw * XToOneDegree, 0.f);

	WorldImageSlot->SetPosition(WorldImageSlotPos);

	int32 RoundMovementOffsetYaw = -(int32)MovementOffsetYaw;
	int32 CurrentDegree = 0;
	if (RoundMovementOffsetYaw >= 0) {
		CurrentDegree = RoundMovementOffsetYaw;


	}
	else {
		CurrentDegree = RoundMovementOffsetYaw + 360;
	}

	FName LabelText = FName();
	FString TempString;

	if (CurrentDegree % 5 == 0) {
		switch (CurrentDegree) {
		case 0:
			LabelText = "N";
			break;
		case 45:
			LabelText = "NE";
			break;
		case 90:
			LabelText = "E";
			break;
		case 135:
			LabelText = "SE";
			break;
		case 180:
			LabelText = "S";
			break;
		case 225:
			LabelText = "SW";
			break;
		case 270:
			LabelText = "W";
			break;
		case 315:
			LabelText = "NW";
			break;
		

		default:
			TempString = FString::FromInt(CurrentDegree);
			LabelText = FName(*TempString);
			break;
		}
	}
	else {
		TempString = FString::FromInt(CurrentDegree);
		LabelText = FName(*TempString);
	}



	FString TempString2 = LabelText.ToString();
	FText TempText = FText::FromString(TempString2);
	CurrentDirection->SetText(TempText);

}


