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




	}





}

void UPUBGA_AnimInstance::NativeInitializeAnimation() {


	ShooterCharacter = Cast<APUBGA_Character>(TryGetPawnOwner());


}
