// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/TimelineComponent.h"
#include "Engine/DataTable.h"
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


	
	UFUNCTION(BlueprintImplementableEvent, Category = CameraRestore)
		void AltReleasedNotif(const FRotator& AltRelRot, const FRotator& AltPreRot);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void ReturnedRotation(FRotator RetRot);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void RestoreAlt();

	FRotator GetControllerRotation();

	void CrouchKeyPressed();

	void ProneKeyPressed();

	void JumpKeyPressed();

	void HandleProneTimeFromTable(int32 Pose1, int32 Pose2);

	FString ProneTimeTablePath;

	UDataTable* ProneTimeTableObject;

	bool bEnableMove = 1;

	float DisableMoveTime = 0.f;

	FTimerHandle TH_DisableMove;

	void EnableMovex();

	UFUNCTION(Category = Input)
		bool LimitPitchAngle(float Axis);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float ProneBottomValue = 350.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float ProneTopValue = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float CrouchBottomValue = 290.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float CrouchTopValue = 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float StandBottomValue = 290.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float StandTopValue = 75.f;

	UFUNCTION(BlueprintImplementableEvent)
		void LimitPitchAngleExcess(bool bGreater, float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float MoveRightAxis = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float MoveForwardAxis = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float CurrentHeight = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float NewHeight = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float OriginalHeight = 0.f;

	UFUNCTION(BlueprintCallable, Category = Cameras)
	void UpdateCameraHeight();

	FString CameraHeightTablePath;

	UDataTable* CameraHeightTableObject;

	UFUNCTION(BlueprintImplementableEvent, Category = Cameras)
		void UpdateCameraHeightWithTL(float OriginalHeightx,float NewHeightx);

	UFUNCTION(BlueprintCallable, Category = Cameras)
		void UpdateCurrentHeight(float UpdatedHeight);

	void WalkKeyPressed();
	void WalkKeyReleased();

	void RunKeyPressed();
	void RunKeyReleased();

	void UpdateWalkSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bWalkPressed=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bRunPressed = 0;

	void ReturnThreeIntegers(int32& HoldWeapon, int32& Posture, int32& MoveState);

	FString WalkSpeedTablePath;

	UDataTable* WalkSpeedTableObject;





};
