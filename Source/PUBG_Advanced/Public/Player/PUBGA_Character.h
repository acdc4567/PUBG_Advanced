// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUBGA_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APUBGA_PlayerController;



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
		USpringArmComponent* CameraBoom;

	

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

	

	UPROPERTY()
		APUBGA_PlayerController* MyPlayerControllerRef;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterPose, meta = (AllowPrivateAccess = "true"))
		bool bIsCrouching = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
		bool bIsProne = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
		bool bIsAiming = 0;



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
	
	FORCEINLINE float GetForwardValue() const { return ForwardValue; }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	//Setters
	void SetIsProne(const bool& Valuex);
	void SetIsCrouching(const bool& Valuex);
	void SetIsAiming(const bool& Valuex);


	virtual void PossessedBy(AController* inController) override;

	UFUNCTION(Category = MouseInput)
		void MouseTurn(float AxisValue);

	UFUNCTION(Category = MouseInput)
		void MouseLookUp(float AxisValue);

	
};
