// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/CaptureActor_UWidget.h"
#include "UI/Capture_Actor_Cpp.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"

void UCaptureActor_UWidget::NativeConstruct() {
	Super::NativeConstruct();

	FTransform Transformx;
	Transformx.SetLocation(FVector(0.f,0.f,-100000.f));
	Transformx.SetRotation(FRotator(84.f, 0.f, 0.f).Quaternion());
	if (CaptureActorClass) {
		CaptureActor = GetWorld()->SpawnActorDeferred<ACapture_Actor_Cpp>(CaptureActorClass, Transformx);
		if (CaptureActor) {
			CaptureActor->FinishSpawning(Transformx);
		}
	}
	


}

void UCaptureActor_UWidget::NativeDestruct() {
	Super::NativeDestruct();
	if (CaptureActor) {
		CaptureActor->Destroy();
	}


}
