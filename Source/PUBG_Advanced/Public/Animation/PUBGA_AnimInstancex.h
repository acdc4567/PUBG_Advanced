// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PUBGA_AnimInstancex.generated.h"

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UPUBGA_AnimInstancex : public UAnimInstance
{
	GENERATED_BODY()


public:
	UPUBGA_AnimInstancex();

	UFUNCTION(BlueprintCallable)
		void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class APUBGA_Characterx* ShooterCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Speed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Direction = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Pitch = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float Yaw = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float ForwardValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float SidewaysVelocity = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsJumping = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsCrouching = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsProne = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsInAir = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsHoldWeapon = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsAim = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsFreeFalling = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsUmbrellaOpen = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsDead = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool bIsPlayingMontage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		int32 AimOffsetType = 0;






};
