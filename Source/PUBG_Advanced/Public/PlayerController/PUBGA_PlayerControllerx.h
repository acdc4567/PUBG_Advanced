// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PUBGA_Structs.h"
#include "Engine/DataTable.h"
#include "PUBGA_PlayerControllerx.generated.h"

class APUBGA_Characterx;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_PlayerControllerx : public APlayerController
{
	GENERATED_BODY()


public:

	APUBGA_PlayerControllerx();

	void OnPossessx(APUBGA_Characterx* inCharacter);

	virtual void SetupInputComponent() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Players)
		APUBGA_Characterx* PlayerCharacterRef;

	void MouseTurn(float Value);
	void MouseLookUp(float Value);

	void MovingOnTheGround(const bool& bForward, const float& AxisValue, const FRotator& ControllerRotation);

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Move)
		float WalkSpeed = 600.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input)
		bool bAltPressed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		FRotator AltPressedRotation = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		FRotator AltReleasedRotation = FRotator::ZeroRotator;

	void AltKeyPressed();
	void AltKeyReleased();

	UFUNCTION(BlueprintImplementableEvent, Category = CameraRestore)
		void AltReleasedNotif(const FRotator& AltRelRot, const FRotator& AltPreRot);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void ReturnedRotation(FRotator RetRot);

	FRotator GetControllerRotation();

	void CrouchKeyPressed();

	void ProneKeyPressed();

	void JumpKeyPressed();

	void HandleProneTimeFromTable(int32 Pose1, int32 Pose2);

	FString ProneTimeTablePath;

	UDataTable* ProneTimeTableObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float DisableMoveTime = 0.f;

	FTimerHandle TH_DisableMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bEnableMove = 1;

	void EnableMove();

	FString CameraHeightTablePath;

	UDataTable* CameraHeightTableObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveForwardAxis = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveRightAxis = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float CurrentHeight = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float NewHeight = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Cameras)
		float OriginalHeight = 0.f;

	UFUNCTION(BlueprintCallable, Category = Cameras)
		void UpdateCameraHeight();

	UFUNCTION(BlueprintImplementableEvent, Category = Cameras)
		void UpdateCameraHeightWithTL(float OriginalHeightx, float NewHeightx);

	UFUNCTION(BlueprintCallable, Category = Cameras)
		void UpdateCurrentHeight(float UpdatedHeight);










};
