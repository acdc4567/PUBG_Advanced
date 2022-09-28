// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/TimelineComponent.h"
#include "Engine/DataTable.h"
#include "PUBGA_Structs.h"
#include "PUBGA_PlayerController.generated.h"

class APUBGA_Character;
class APickUpBase;
class APUBGA_PlayerState;
class APUBGA_GameModeBase;
class APickUpWeapon;
class AItemWeapon;


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

	FName GenerateSN();


protected:

	virtual void BeginPlay() override;

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

	void AimKeyPressed();
	void AimKeyReleased();

	void UpdateWalkSpeed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bWalkPressed=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		bool bRunPressed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponAiming)
		bool bHoldAiming = 0;


	void ReturnThreeIntegers(int32& HoldWeapon, int32& Posture, int32& MoveState);

	FString WalkSpeedTablePath;

	UDataTable* WalkSpeedTableObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		TArray<APickUpBase*> PickupItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		TArray<APickUpBase*> ItemsInRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		float RightPressedTime=0.f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		APUBGA_PlayerState* PlayerStateRef;

	UFUNCTION()
		void Event_WeaponChanged(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand);

	UFUNCTION()
		void Event_EquipmentChanged(AItemBase* Equipment, bool bIsAdd);

	UFUNCTION()
		void Event_FashionChanged(AItemBase* Fashion, bool bIsAdd);

	UFUNCTION()
		void Event_ItemsChanged(AItemBase* Item, bool bIsAdd);

	UFUNCTION()
		void Event_WeaponAccChanged( AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType);


	UFUNCTION()
		void Event_AmmoChanged(bool bIsTrue);


	UFUNCTION(BlueprintImplementableEvent)
		void Event_ItemsChanges();


	UFUNCTION()
		void Event_OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void SetPickupItems(TArray<APickUpBase*> Items);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameMode)
		APUBGA_GameModeBase* GameModeRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameMode)
		TArray<APickUpBase*> GameModeGeneratedItems;

	void ExecBeginOverlap(APickUpBase* PickupObject);

	void ExecEndOverlap(APickUpBase* PickupObject);

	void OutlineItem(APickUpBase* Item);

	void TargetingItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameMode)
		APickUpBase* ReadyPickupItem;

	EWeaponPosition AutoPosition(bool & bIsOnHand);

	void AssignPosition(const EWeaponPosition& Assign, EWeaponPosition& Position,bool & bIsOnHand);

	APickUpBase* SpawnPickupItems(AItemBase* ItemBase);

	UFUNCTION(BlueprintCallable)
		void SpawnPickUpItem( AItemBase* ItemBase, APickUpBase*& PU);

	UFUNCTION(BlueprintCallable)
		void DiscardWeapon(AItemWeapon* ItemWeapon);

	

	void DiscardKeyPressed();

	void PickupWeapon(APickUpWeapon* PickupWeaponx, bool bIsAssign, EWeaponPosition Positionx);

	bool PickUpItemSuccess();

	void InteractionKeyPressed();

	void UpdateCharacterGunState();

	void TakeBackKeyPressed();

	void Keyboard1KeyPressed();

	void Keyboard2KeyPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameMode)
		AItemWeapon* ReadyEquipWeapon;

	bool PickupGoods(APickUpBase* PUItem);

	UFUNCTION(BlueprintCallable)
		void DiscardItem(AItemBase* IBItem);

	bool DiscardEquipment(AItemBase* IBItem, bool bIsCheck);

	bool PickupEquipment(AItemBase* IBItem);

	void DiscardFashion(AItemBase* IBItem);

	void PickupFashion(APickUpBase* PUItem);

	UFUNCTION(BlueprintCallable)
		bool EquipAccessories(AItemBase* IBItemBase,bool bIsFromGround,AItemWeapon* IWeapon);

	UFUNCTION(BlueprintCallable)
		bool RemoveAccessory(AItemBase* ItemAcc, bool bIsToGround, AItemWeapon* Weapon);

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponAiming)
		float AccurateRemaining=0.f;

	FString AimAccuratelyTablePath;

	UDataTable* AimAccuratelyTableObject;

	FSTR_AimAccurately* AimAccuratelyDatas=nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponAiming)
		float AimAccuratelyRemaining = 0.f;

	void UpdateAccurateRemaining(float Delta);

	void ShootModeKeyPressed();

	void FireKeyPressed();

	void FireKeyReleased();

	void ReleaseFire();

	void StopAimState();

	void ReloadKeyPressed();





public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Backpack)
		int32 DefaultCapacity = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunStandName = "Socket_Gun_Stand";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunAimName = "Socket_Gun_Aim";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunReloadName = "Socket_Gun_Reload";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunProneIdleName = "Socket_Gun_ProneIdle";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunProneFBName = "Socket_Gun_ProneFB";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunProneOtherName = "Socket_Gun_ProneOther";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName GunCrouchName = "Socket_Gun_Crouch";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName BackLeftNName = "Socket_BackLeft_Normal";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName BackRightNName = "Socket_BackRight_Normal";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName BackLeftBName = "Socket_BackLeft_Backpack";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName BackRightBName = "Socket_BackRight_Backpack";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName HelmetName = "Socket_Helmet";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName VestName = "Socket_Vest";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SocketNames)
		FName BackpackName = "Socket_Backpack";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ReloadTimes)
		float ReplaceClipTime_Stand = 2.167f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ReloadTimes)
		float ReplaceClipTime_Prone = 2.4f;


	void TakeBackWeapon();

	void EquipWeapon();

	FName CalculateHoldGunSocket();

	FORCEINLINE APUBGA_PlayerState* GetPlayerStateRef() const { return PlayerStateRef; }

	void ReverseHoldAiming();

	void Event_ReloadEnd();

	void ExecuteReload();

	FORCEINLINE void SetRunPressed(bool bValue) { bRunPressed = bValue; }

	UFUNCTION(BlueprintCallable)
		void RecoilInput(float YawVal,float PitchVal);

	FORCEINLINE bool GetIsHoldAiming() const { return bHoldAiming; }

	FORCEINLINE float GetMoveForwardAxis() const { return MoveForwardAxis; }
	FORCEINLINE float GetMoveRightAxis() const { return MoveRightAxis; }

	FORCEINLINE float GetRightPressedTime() const { return RightPressedTime; }




};
