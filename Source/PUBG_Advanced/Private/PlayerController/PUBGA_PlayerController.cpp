// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerController.h"
#include "Player/PUBGA_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



APUBGA_PlayerController::APUBGA_PlayerController() {


}

void APUBGA_PlayerController::OnPossessx1(APUBGA_Character* inCharacter) {

	MyCharacterRef = inCharacter;

}

void APUBGA_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAxis("Turn", this, &APUBGA_PlayerController::MouseTurn);
	InputComponent->BindAxis("LookUp", this, &APUBGA_PlayerController::MouseLookUp);

	InputComponent->BindAxis("MoveForward", this, &APUBGA_PlayerController::MoveFwd);
	InputComponent->BindAxis("MoveRight", this, &APUBGA_PlayerController::MoveRt);

	InputComponent->BindAction("Alt", IE_Pressed,this, &APUBGA_PlayerController::AltKeyPressed);
	InputComponent->BindAction("Alt", IE_Released, this, &APUBGA_PlayerController::AltKeyReleased);


}

void APUBGA_PlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (MyCharacterRef) {
		if (!bAltPressed) {
			const FRotator Rotation{ GetControlRotation() };
			const FRotator NewRotation{ 0,Rotation.Yaw,0 };
			MyCharacterRef->SetActorRotation(NewRotation);
			
		}
		
	}



}


void APUBGA_PlayerController::UpdateDissolveMaterial(float DissolveValue) {
	
	FRotator NewRotation= FRotator(FQuat::Slerp(AltReleasedRotation.Quaternion(), AltPressedRotation.Quaternion(), DissolveValue));
	SetControlRotation(NewRotation);
}

void APUBGA_PlayerController::StartDissolve() {

	DissolveTrack.BindDynamic(this, &APUBGA_PlayerController::UpdateDissolveMaterial);
	if (DissolveCurve) {
		DissolveTimeline->AddInterpFloat(DissolveCurve, DissolveTrack);
		DissolveTimeline->PlayFromStart();
	}

}



void APUBGA_PlayerController::MouseTurn(float AxisValue) {
	if (!MyCharacterRef)return;
	MyCharacterRef->MouseTurn(AxisValue);

}


void APUBGA_PlayerController::MouseLookUp(float AxisValue) {
	if (!MyCharacterRef)return;
	MyCharacterRef->MouseLookUp(AxisValue);

}

void APUBGA_PlayerController::MoveFwd(float AxisValue) {
	MovingOnTheGround(1, AxisValue,GetControllerRotation());
}

void APUBGA_PlayerController::MoveRt(float AxisValue) {
	MovingOnTheGround(0, AxisValue,GetControllerRotation());
}



void APUBGA_PlayerController::MovingOnTheGround(const bool& bForward, const float& AxisValue, const FRotator& ControllerRotation) {
	if (!MyCharacterRef)return;

	const FRotator Rotation = ControllerRotation;
	const FRotator YawRotation{ 0,Rotation.Yaw,0 };
	
	//SmoothIncrease
	const float VelocitySize = MyCharacterRef->GetCharacterMovement()->Velocity.Size();
	if (VelocitySize+ 5.f<=WalkSpeed) {
		MyCharacterRef->GetCharacterMovement()->MaxWalkSpeed = VelocitySize + 5.f;
	}
	else {
		MyCharacterRef->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}



	if (bForward) {
		
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		MyCharacterRef->AddMovementInput(Direction, AxisValue);

	}
	else {
		
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		MyCharacterRef->AddMovementInput(Direction, AxisValue);
	}
	

}

void APUBGA_PlayerController::AltKeyPressed() {
	//UE_LOG(LogTemp, Warning, TEXT("AltPressed"));
	if (!MyCharacterRef)return;
	bAltPressed = 1;
	AltPressedRotation = MyCharacterRef->GetCameraBoom()->GetTargetRotation();

}

void APUBGA_PlayerController::AltKeyReleased() {
	
	if (!MyCharacterRef)return;
	//bAltPressed = 0;
	AltReleasedRotation = MyCharacterRef->GetCameraBoom()->GetTargetRotation();
	AltReleasedNotif(AltReleasedRotation,AltPressedRotation );
}

void APUBGA_PlayerController::ReturnedRotation(FRotator RetRot) {
	SetControlRotation(RetRot);
}


void APUBGA_PlayerController::RestoreAlt() {
	bAltPressed = 0;
}


FRotator APUBGA_PlayerController::GetControllerRotation() {
	return bAltPressed ? AltPressedRotation : GetControlRotation();
}




