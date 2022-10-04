// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"

#include "CaptureActor_UWidget.generated.h"



class ACapture_Actor_Cpp;
class APUBGA_PlayerController;
class APUBGA_PlayerState;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UCaptureActor_UWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		ACapture_Actor_Cpp* CaptureActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		TSubclassOf< ACapture_Actor_Cpp> CaptureActorClass;




};
