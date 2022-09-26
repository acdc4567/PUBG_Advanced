// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Animation/PUBGA_ArmsAnimInstance.h"
#include "Player/PUBGA_Character.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Items/ItemWeaponAcc.h"
#include "Items/ItemWeapon.h"



UPUBGA_ArmsAnimInstance::UPUBGA_ArmsAnimInstance() {


}
void UPUBGA_ArmsAnimInstance::UpdateAnimationProperties(float DeltaTime) {
	if (ShooterCharacter == nullptr) {
		ShooterCharacter = Cast<APUBGA_Character>(TryGetPawnOwner());
	}
	if (ShooterCharacter) {
		const FVector Velocity = ShooterCharacter->GetVelocity();
		
		Speed = Velocity.Size();

		bIsAiming = ShooterCharacter->GetIsAiming();

		if (ShooterCharacter->GetIsAimAccurate()) {
			AimRate = 0.f;
		}
		else {
			AimRate = 0.8f;
		}

		if (!bIsCasted) {
			PlayerStateRef = ShooterCharacter->GetPlayerStateRef();
			if (PlayerStateRef) {
				
				bIsCasted = 1;
			}
			
		}

		if (PlayerStateRef) {
			if (PlayerStateRef->GetHoldGun()) {
				if (PlayerStateRef->GetHoldGun()->AccSightObj) {
					if (PlayerStateRef->GetHoldGun()->AccSightObj->Datas->SightMultiple == 4) {
						AimRate = 0.f;
					}
				}
			}
		}



	}


}




void UPUBGA_ArmsAnimInstance::NativeInitializeAnimation() {
	ShooterCharacter = Cast<APUBGA_Character>(TryGetPawnOwner());

	

}
