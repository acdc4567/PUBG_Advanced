// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APUBGA_PlayerController;
class USkeletalMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UTexture;
class APickUpBase;
class APUBGA_PlayerState;
class AItemWeapon;
class UAnimMontage;



UCLASS()
class PUBG_ADVANCED_API APUBGA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APUBGA_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* FPS_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USkeletalMeshComponent* FPS_Arms;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsDead = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsHoldWeapon = 0;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsFiring = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsEquip = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsReload = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = OnTheAir)
		bool bIsOnTheAir = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = OnTheAir)
		bool bIsFreeFalling = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = OnTheAir)
		bool bIsUmbrellaOpen = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = OnTheAir)
		float ForwardValue = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		bool bIsPlayingMontage = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		bool bIsSightAiming = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Hair;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_UnderwearTop;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_UnderwearBottom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_ClothTop;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_ClothBottom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Whole;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Shoes;




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UFUNCTION(BlueprintCallable,Category=SkeletalMeshes)
	void InitSkeletalMesh();

	UFUNCTION(BlueprintCallable,Category=SkeletalMeshes)
	void ReplaceSkeletalMesh(EFashionType FashionType,FName Namex);

	USkeletalMesh* GetFashionDatas(FName ID);

	UTexture* GetFashionDatasTexture(FName ID);


	FString ItemFashionTablePath;

	UDataTable* ItemFashionTableObject;

	UMaterialInstanceDynamic* SkinMatRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UTexture* SkinMatTest;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		APUBGA_PlayerState* PlayerStateRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* StandEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* StandUnEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* StandReloadMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* StandFireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* StandUseMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* CrouchEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* CrouchUnEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* CrouchReloadMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* CrouchFireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* CrouchUseMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ProneEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ProneUnEquipMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ProneReloadMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ProneFireMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ProneUseMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* ArmsFireMontage;

	void InitAnimations();

	void EquipNotifyHandle(USkeletalMeshComponent* MyMesh);

	void EquipFinishedNotifyHandle(USkeletalMeshComponent* MyMesh);

	void UnEquipNotifyHandle(USkeletalMeshComponent* MyMesh);

	void UnEquipFinishedNotifyHandle(USkeletalMeshComponent* MyMesh);

	void FireEndNotifyHandle(USkeletalMeshComponent* MyMesh);

	void ReloadEndNotifyHandle(USkeletalMeshComponent* MyMesh);

	
	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void ReturnedCameraLocation(FVector RetVec);

	
	FString ArmsLocationTablePath;

	UDataTable* ArmsLocationTableObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AimsAccurately)
		bool bIsAimAccurate = 0;





private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterPose, meta = (AllowPrivateAccess = "true"))
		bool bIsCrouching = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
		bool bIsProne = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
		bool bIsAiming = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
		EMontageType PlayingMontageType;
	




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Getters
	FORCEINLINE bool GetIsCrouching() const { return bIsCrouching; }
	FORCEINLINE bool GetIsProne() const { return bIsProne; }
	FORCEINLINE bool GetIsDead() const { return bIsDead; }
	FORCEINLINE bool GetIsHoldWeapon() const { return bIsHoldWeapon; }
	FORCEINLINE bool GetIsAiming() const { return bIsAiming; }
	FORCEINLINE bool GetIsFiring() const { return bIsFiring; }
	FORCEINLINE bool GetIsEquip() const { return bIsEquip; }
	FORCEINLINE bool GetIsReload() const { return bIsReload; }
	FORCEINLINE bool GetIsOnTheAir() const { return bIsOnTheAir; }
	FORCEINLINE bool GetIsFreeFalling() const { return bIsFreeFalling; }
	FORCEINLINE bool GetIsUmbrellaOpen() const { return bIsUmbrellaOpen; }
	FORCEINLINE bool GetIsPlayingMontage() const { return bIsPlayingMontage; }
	FORCEINLINE bool GetIsSightAiming() const { return bIsSightAiming; }
	FORCEINLINE bool GetIsAimAccurate() const { return bIsAimAccurate; }

	FORCEINLINE float GetForwardValue() const { return ForwardValue; }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UCameraComponent* GetFPS_Camera() const { return FPS_Camera; }

	FORCEINLINE EMontageType GetPlayingMontageType() const { return PlayingMontageType; }

	FORCEINLINE APUBGA_PlayerState* GetPlayerStateRef() const { return PlayerStateRef; }

	FORCEINLINE USkeletalMeshComponent* GetFPS_Arms() const { return FPS_Arms; }

	FORCEINLINE UAnimMontage* GetArmsFireMontage() const { return ArmsFireMontage; }


	//Setters
	void SetIsProne(const bool& Valuex);
	void SetIsCrouching(const bool& Valuex);
	void SetIsAiming(const bool& Valuex);
	FORCEINLINE void SetIsPlayingMontage(bool bValue) { bIsPlayingMontage = bValue; }
	FORCEINLINE void SetIsHoldWeapon(bool bValue) { bIsHoldWeapon = bValue; }
	FORCEINLINE void SetIsSightAiming(bool bValue) { bIsSightAiming = bValue; }
	FORCEINLINE void SetIsAccurateAiming(bool bValue) { bIsAimAccurate = bValue; }



	virtual void PossessedBy(AController* inController) override;

	UFUNCTION(Category = MouseInput)
		void MouseTurn(float AxisValue);

	UFUNCTION(Category = MouseInput)
		void MouseLookUp(float AxisValue);


	void UpdateWeaponDisplay(FName HoldSocket);

	void Attach(AItemWeapon* WeaponToAttach, FName SocksName);

	void UpdateEquipmentDisplay();

	void ClearFashion();

	void UpdateFashionDisplay();

	void PlayMontage(EMontageType MontageType,float InPlayRates=1.f);

	UFUNCTION(BlueprintImplementableEvent, Category = CameraRestore)
		void HoldAiming(bool bForward);

	UFUNCTION(BlueprintCallable, Category = CameraRestore)
		void SwitchCamera(bool bIsFirst);

	UFUNCTION(BlueprintImplementableEvent, Category = CameraRestore)
		void SetIsSighAiming(bool bIsSighAiming);




};
