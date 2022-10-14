// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUBGA_Characterx.generated.h"


class USpringArmComponent;
class UCameraComponent;
class APUBGA_PlayerControllerx;



UCLASS()
class PUBG_ADVANCED_API APUBGA_Characterx : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APUBGA_Characterx();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USceneComponent* BowStrap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UStaticMeshComponent* Quiver;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsDead = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState)
		bool bIsHoldWeapon = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
		bool bIsFiring = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
		bool bIsEquip = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterState)
		bool bIsReload = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OnTheAir)
		bool bIsOnTheAir = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OnTheAir)
		bool bIsFreeFalling = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OnTheAir)
		bool bIsUmbrellaOpen = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OnTheAir)
		float ForwardValue = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animation)
		bool bIsPlayingMontage = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
		bool bIsSightAiming = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
		bool bIsCrouching = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
		bool bIsProne = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
		bool bIsAiming = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerControllerx* PlayerControllerRef;


	












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
	//FORCEINLINE bool GetIsAimAccurate() const { return bIsAimAccurate; }

	FORCEINLINE float GetForwardValue() const { return ForwardValue; }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	
	//Setters

	FORCEINLINE void SetIsProne(bool bValue) { bIsProne = bValue; }
	FORCEINLINE void SetIsCrouching(bool bValue) { bIsCrouching = bValue; }
	FORCEINLINE void SetIsAiming(bool bValue) { bIsAiming = bValue; }
	FORCEINLINE void SetIsPlayingMontage(bool bValue) { bIsPlayingMontage = bValue; }
	FORCEINLINE void SetIsHoldWeapon(bool bValue) { bIsHoldWeapon = bValue; }
	FORCEINLINE void SetIsSightAiming(bool bValue) { bIsSightAiming = bValue; }
	//FORCEINLINE void SetIsAccurateAiming(bool bValue) { bIsAimAccurate = bValue; }
	

	virtual void PossessedBy(AController* inController) override;

	void MouseTurn(float AxisValue);
	void MouseLookUp(float AxisValue);




};
