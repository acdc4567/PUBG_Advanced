// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/TimelineComponent.h"
#include "PUBGA_PlayerController.generated.h"

class APUBGA_Character;

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	


public:
	APUBGA_PlayerController();

	void OnPossessx1(APUBGA_Character* inCharacter);
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Players)
		APUBGA_Character* MyCharacterRef;

	UFUNCTION()
	void MouseTurn(float AxisValue);
	UFUNCTION()
	void MouseLookUp(float AxisValue);

	void MoveFwd(float AxisValue);
	void MoveRt(float AxisValue);

	void MovingOnTheGround(const bool& bForward,const float& AxisValue,const FRotator& ControllerRotation);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float WalkSpeed=600.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bAltPressed = 0;

	void AltKeyPressed();
	void AltKeyReleased();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		FRotator AltPressedRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		FRotator AltReleasedRotation;

	//TimelineComponents
	UPROPERTY(VisibleAnywhere)
		UTimelineComponent* DissolveTimeline;

	FOnTimelineFloat DissolveTrack;

	UFUNCTION()
		void UpdateDissolveMaterial(float DissolveValue);

	void StartDissolve();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UCurveFloat* DissolveCurve;


	//
	UFUNCTION(BlueprintImplementableEvent, Category = CameraRestore)
		void AltReleasedNotif(const FRotator& AltRelRot, const FRotator& AltPreRot);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void ReturnedRotation(FRotator RetRot);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void RestoreAlt();

	FRotator GetControllerRotation();


};
