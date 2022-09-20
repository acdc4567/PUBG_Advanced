// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerController.h"
#include "Player/PUBGA_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PUBGA_Structs.h"


APUBGA_PlayerController::APUBGA_PlayerController() {
	ProneTimeTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ProneTimes.DT_ProneTimes'");
	ProneTimeTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ProneTimeTablePath));

	CameraHeightTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_CameraHeight.DT_CameraHeight'");
	CameraHeightTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *CameraHeightTablePath));

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

	InputComponent->BindAction("Crouch", IE_Pressed, this, &APUBGA_PlayerController::CrouchKeyPressed);
	
	InputComponent->BindAction("Prone", IE_Pressed, this, &APUBGA_PlayerController::ProneKeyPressed);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APUBGA_PlayerController::JumpKeyPressed);





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
	MyCharacterRef->MouseTurn(AxisValue );
	

	


}


void APUBGA_PlayerController::MouseLookUp(float AxisValue) {
	if (!MyCharacterRef)return;
	MyCharacterRef->MouseLookUp(AxisValue);
	
}

void APUBGA_PlayerController::MoveFwd(float AxisValue) {
	if (MoveForwardAxis != AxisValue) {
		MoveForwardAxis = AxisValue;
		UpdateCameraHeight();
	}

	if (bEnableMove) {
		MovingOnTheGround(1, AxisValue, GetControllerRotation());
	}
	
}

void APUBGA_PlayerController::MoveRt(float AxisValue) {
	if (MoveRightAxis != AxisValue) {
		MoveRightAxis = AxisValue;
		UpdateCameraHeight();

	}

	if (bEnableMove) {
		MovingOnTheGround(0, AxisValue, GetControllerRotation());
	}

	
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


void APUBGA_PlayerController::CrouchKeyPressed() {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsProne()) {
		MyCharacterRef->SetIsProne(0);
		MyCharacterRef->SetIsCrouching(1);
		HandleProneTimeFromTable(3, 2);
	}
	else {
		if (MyCharacterRef->GetIsCrouching()) {
			MyCharacterRef->SetIsCrouching(0);
		}
		else {
			MyCharacterRef->SetIsCrouching(1);
		}

	}
	UpdateCameraHeight();

}


void APUBGA_PlayerController::ProneKeyPressed() {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsProne()) {
		MyCharacterRef->SetIsProne(0);
		HandleProneTimeFromTable(3, 1);
	}
	else {
		if (MyCharacterRef->GetIsCrouching()) {
			MyCharacterRef->SetIsCrouching(0);
			MyCharacterRef->SetIsProne(1);
			MyCharacterRef->SetIsAiming(0);
			HandleProneTimeFromTable(3, 2);
		}
		else {
			MyCharacterRef->SetIsProne(1);
			MyCharacterRef->SetIsAiming(0);
			HandleProneTimeFromTable(1, 3);
		}
	}
	
	UpdateCameraHeight();
}

void APUBGA_PlayerController::JumpKeyPressed() {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsProne()) {
		MyCharacterRef->SetIsProne(0);
		MyCharacterRef->SetIsCrouching(1);
	}
	else {
		if (MyCharacterRef->GetIsCrouching()) {
			MyCharacterRef->SetIsCrouching(0);
		}
		else {
			MyCharacterRef->Jump();
		}
	}

	UpdateCameraHeight();

}


void APUBGA_PlayerController::HandleProneTimeFromTable(int32 Pose1, int32 Pose2) {

	//PoseNumber1=Stand,PoseNumber2=Crouch,PoseNumber3=Prone

	FSTR_ProneTimes* ProneTimeRow = nullptr;
	if (Pose1 == 3 && Pose2 == 2) {
		if (MyCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_prone_crouch"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_prone_crouch"), TEXT(""));

		}
	}
	if (Pose1 == 3 && Pose2 == 1) {
		if (MyCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_prone_stand"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_prone_stand"), TEXT(""));

		}
	}
	if (Pose1 == 2 && Pose2 == 3) {
		if (MyCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_crouch_prone"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_crouch_prone"), TEXT(""));

		}
	}
	if (Pose1 == 1 && Pose2 == 3) {
		if (MyCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_stand_prone"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_stand_prone"), TEXT(""));

		}
	}
	if (ProneTimeRow) {
		DisableMoveTime = ProneTimeRow->Sec;

	}


	bEnableMove = 0;
	GetWorldTimerManager().SetTimer(TH_DisableMove, this, &APUBGA_PlayerController::EnableMovex, DisableMoveTime, false);


}


void APUBGA_PlayerController::EnableMovex() {
	bEnableMove = 1;
}



bool APUBGA_PlayerController::LimitPitchAngle(float Axis) {
	float BottomValue;
	float TopValue;
	if (MyCharacterRef->GetIsProne()) {
		BottomValue = ProneBottomValue;
		TopValue = ProneTopValue;

	}
	else if (MyCharacterRef->GetIsCrouching()) {
		BottomValue = CrouchBottomValue;
		TopValue = CrouchTopValue;
	}
	else {
		BottomValue = StandBottomValue;
		TopValue = StandTopValue;
	}


	float ControllerPitch = GetControlRotation().Pitch;
	float ControllerYaw = GetControlRotation().Yaw;
	float ControllerRoll = GetControlRotation().Roll;

	float Excess = Axis ;
	if (!(ControllerPitch > BottomValue || ControllerPitch < TopValue)) {
		if (FMath::Abs(ControllerPitch - TopValue) < FMath::Abs(ControllerPitch - BottomValue)) {
			LimitPitchAngleExcess(1, TopValue);
		}
		else {
			LimitPitchAngleExcess(0, BottomValue);

		}

	}

	if (ControllerPitch + Excess > BottomValue || ControllerPitch + Excess < TopValue) {
		return true;
	}
	else {
		return false;
	}


	return true;
}

void APUBGA_PlayerController::UpdateCameraHeight() {
	FSTR_CameraHeight* CameraHeightRow = nullptr;
	if (MyCharacterRef->GetIsCrouching()) {
		if (!(MyCharacterRef->GetIsHoldWeapon()) && (MoveForwardAxis != 0 || MoveRightAxis != 0)) {
			
			CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Crouch_Normal_Move"), TEXT(""));
			if (CameraHeightRow) {
				NewHeight = CameraHeightRow->Height;
			}

		}
		else if ((MyCharacterRef->GetIsHoldWeapon()) && (MoveForwardAxis != 0 || MoveRightAxis != 0)) {
			CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Crouch_Rifle_Move"), TEXT(""));
			if (CameraHeightRow) {
				NewHeight = CameraHeightRow->Height;
			}
		}
		else {
			CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Crouch"), TEXT(""));
			if (CameraHeightRow) {
				NewHeight = CameraHeightRow->Height;
			}
		}

	}
	else if(MyCharacterRef->GetIsProne()) {
		CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Prone"), TEXT(""));
		if (CameraHeightRow) {
			NewHeight = CameraHeightRow->Height;
		}
	}
	else {
		CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Stand"), TEXT(""));
		if (CameraHeightRow) {
			NewHeight = CameraHeightRow->Height;
		}
	}

	if (CurrentHeight != NewHeight) {
		 OriginalHeight= CurrentHeight;
		UpdateCameraHeightWithTL(OriginalHeight, NewHeight);
	}
	





}

void APUBGA_PlayerController::UpdateCurrentHeight(float UpdatedHeight) {
	CurrentHeight = UpdatedHeight;
}






