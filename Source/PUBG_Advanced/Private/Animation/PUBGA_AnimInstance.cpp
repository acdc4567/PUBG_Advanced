// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Animation/PUBGA_AnimInstance.h"
#include "Player/PUBGA_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"




UPUBGA_AnimInstance::UPUBGA_AnimInstance() {




}

void UPUBGA_AnimInstance::UpdateAnimationProperties(float DeltaTime) {

	if (ShooterCharacter == nullptr) {
		ShooterCharacter = Cast<APUBGA_Character>(TryGetPawnOwner());
	}
	if (ShooterCharacter) {
		bIsPlayingMontage= ShooterCharacter->GetIsPlayingMontage();
		
		bIsCrouching = ShooterCharacter->GetIsCrouching();

		bIsProne = ShooterCharacter->GetIsProne();

		bIsDead = ShooterCharacter->GetIsDead();

		bIsHoldWeapon = ShooterCharacter->GetIsHoldWeapon();

		bIsAim = ShooterCharacter->GetIsAiming();

		const FVector Velocity=ShooterCharacter->GetVelocity() ;
		//Velocity.Z = 0;
		Speed = Velocity.Size();
		const FRotator ShooterRotation= ShooterCharacter->GetActorRotation();
		const FQuat ShooterRotationQuat = ShooterCharacter->GetActorQuat();
		Direction = CalculateDirection(Velocity,ShooterRotation);
		const FRotator ShooterControlRot = ShooterCharacter->GetControlRotation();
		Pitch = UKismetMathLibrary::NormalizedDeltaRotator(ShooterControlRot, ShooterRotation).Pitch;
		Yaw = UKismetMathLibrary::NormalizedDeltaRotator(ShooterControlRot, ShooterRotation).Yaw;
		
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		bIsFreeFalling = ShooterCharacter->GetIsFreeFalling();

		bIsUmbrellaOpen = ShooterCharacter->GetIsUmbrellaOpen();

		ForwardValue = ShooterCharacter->GetForwardValue();

		SidewaysVelocity = UKismetMathLibrary::Quat_UnrotateVector(ShooterRotationQuat,Velocity).Y;
			
		if (bIsInAir && bIsProne) {
			AimOffsetType = 0;
		}
		else {
			if (bIsCrouching) {
				if (bIsHoldWeapon) {
					if (bIsAim) {
						AimOffsetType = 6;
					}
					else {
						AimOffsetType = 4;
					}
				}
				else {
					AimOffsetType = 2;
				}
			}
			else {
				if (bIsHoldWeapon) {
					if (bIsAim) {
						AimOffsetType = 5;
					}
					else {
						AimOffsetType = 3;
					}
				}
				else {
					AimOffsetType = 1;
				}
			}
		}
		
		



	}





}

void UPUBGA_AnimInstance::NativeInitializeAnimation() {


	ShooterCharacter = Cast<APUBGA_Character>(TryGetPawnOwner());


}
