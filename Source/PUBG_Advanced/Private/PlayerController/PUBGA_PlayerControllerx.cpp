// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerControllerx.h"
#include "Player/PUBGA_Characterx.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



APUBGA_PlayerControllerx::APUBGA_PlayerControllerx() {
	ProneTimeTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ProneTimes.DT_ProneTimes'");
	ProneTimeTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ProneTimeTablePath));

	CameraHeightTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_CameraHeight.DT_CameraHeight'");
	CameraHeightTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *CameraHeightTablePath));

}

void APUBGA_PlayerControllerx::OnPossessx(APUBGA_Characterx* inCharacter) {
	if (!inCharacter)return;
	PlayerCharacterRef = inCharacter;
}

void APUBGA_PlayerControllerx::SetupInputComponent() {

	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAxis("Turn", this, &APUBGA_PlayerControllerx::MouseTurn);
	InputComponent->BindAxis("LookUp", this, &APUBGA_PlayerControllerx::MouseLookUp);

	InputComponent->BindAxis("MoveForward", this, &APUBGA_PlayerControllerx::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APUBGA_PlayerControllerx::MoveRight);

	InputComponent->BindAction("Alt", IE_Pressed, this, &APUBGA_PlayerControllerx::AltKeyPressed);
	InputComponent->BindAction("Alt", IE_Released, this, &APUBGA_PlayerControllerx::AltKeyReleased);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &APUBGA_PlayerControllerx::CrouchKeyPressed);

	InputComponent->BindAction("Prone", IE_Pressed, this, &APUBGA_PlayerControllerx::ProneKeyPressed);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APUBGA_PlayerControllerx::JumpKeyPressed);




}

void APUBGA_PlayerControllerx::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (PlayerCharacterRef) {
		if (!bAltPressed) {
			const FRotator Rotation{ GetControlRotation() };
			const FRotator NewRotation{ 0.f,Rotation.Yaw,0.f };

			PlayerCharacterRef->SetActorRotation(NewRotation);
		}
		

	}



}

void APUBGA_PlayerControllerx::BeginPlay() {
	Super::BeginPlay();

	



}

void APUBGA_PlayerControllerx::MouseTurn(float Value) {
	if (!PlayerCharacterRef)return;
	PlayerCharacterRef->MouseTurn(Value * .5f);

}

void APUBGA_PlayerControllerx::MouseLookUp(float Value) {
	if (!PlayerCharacterRef)return;
	PlayerCharacterRef->MouseLookUp(Value * .5f);

}

void APUBGA_PlayerControllerx::MovingOnTheGround(const bool& bForward, const float& AxisValue, const FRotator& ControllerRotation) {

	if (!PlayerCharacterRef)return;

	const FRotator Rotation = ControllerRotation;
	const FRotator YawRotation{ 0,Rotation.Yaw,0 };
	
	//Smooth Increase
	float TempSpeed = PlayerCharacterRef->GetCharacterMovement()->Velocity.Size()+5.f;
	if (TempSpeed <= WalkSpeed) {
		PlayerCharacterRef->GetCharacterMovement()->MaxWalkSpeed = TempSpeed;
	}
	else {
		PlayerCharacterRef->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	
	
	if (bForward) {

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
		PlayerCharacterRef->AddMovementInput(Direction, AxisValue);

	}
	else {

		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };
		PlayerCharacterRef->AddMovementInput(Direction, AxisValue);
	}



}

void APUBGA_PlayerControllerx::MoveForward(float Value) {
	
	if (MoveForwardAxis != Value) {
		MoveForwardAxis = Value;
		UpdateCameraHeight();
		
	}
	
	if (bEnableMove) {
		MovingOnTheGround(1, Value, GetControllerRotation());
	}
	
}

void APUBGA_PlayerControllerx::MoveRight(float Value) {
	
	if (MoveRightAxis != Value) {
		MoveRightAxis = Value;
		UpdateCameraHeight();

	}
	
	if (bEnableMove) {
		MovingOnTheGround(0, Value, GetControllerRotation());
	}
	

}

void APUBGA_PlayerControllerx::AltKeyPressed() {
	if (!PlayerCharacterRef)return;
	bAltPressed = 1;
	AltPressedRotation = PlayerCharacterRef->GetCameraBoom()->GetTargetRotation();


}

void APUBGA_PlayerControllerx::AltKeyReleased() {
	if (!PlayerCharacterRef)return;
	//bAltPressed = 0;

	AltReleasedRotation= PlayerCharacterRef->GetCameraBoom()->GetTargetRotation();
	AltReleasedNotif(AltReleasedRotation,AltPressedRotation);

}

void APUBGA_PlayerControllerx::ReturnedRotation(FRotator RetRot) {

	SetControlRotation(RetRot);

}

FRotator APUBGA_PlayerControllerx::GetControllerRotation() {
	
	if (bAltPressed) {
		return AltPressedRotation;
	}
	else {
		return GetControlRotation();
	}
	return FRotator();
}

void APUBGA_PlayerControllerx::CrouchKeyPressed() {
	if (!PlayerCharacterRef)return;

	if (PlayerCharacterRef->GetIsProne()) {
		PlayerCharacterRef->SetIsProne(0);
		PlayerCharacterRef->SetIsCrouching(1);
		HandleProneTimeFromTable(3, 2);

	}
	else {
		if (PlayerCharacterRef->GetIsCrouching()) {
			PlayerCharacterRef->SetIsCrouching(0);
		}
		else {
			PlayerCharacterRef->SetIsCrouching(1);
		}
	}

	UpdateCameraHeight();


}

void APUBGA_PlayerControllerx::ProneKeyPressed() {
	if (!PlayerCharacterRef)return;
	if (PlayerCharacterRef->GetIsProne()) {
		PlayerCharacterRef->SetIsProne(0);
		HandleProneTimeFromTable(3, 1);
	}
	else {
		if (PlayerCharacterRef->GetIsCrouching()) {
			PlayerCharacterRef->SetIsCrouching(0);
			PlayerCharacterRef->SetIsProne(1);
			PlayerCharacterRef->SetIsAiming(0);
			HandleProneTimeFromTable(3, 2);
		}
		else {
			PlayerCharacterRef->SetIsProne(1);
			PlayerCharacterRef->SetIsAiming(0);
			HandleProneTimeFromTable(1, 3);
		}

	}

	UpdateCameraHeight();
}

void APUBGA_PlayerControllerx::JumpKeyPressed() {

	if (!PlayerCharacterRef)return;
	if (PlayerCharacterRef->GetIsProne()) {
		PlayerCharacterRef->SetIsProne(0);
		PlayerCharacterRef->SetIsCrouching(1);

	}
	else {
		if (PlayerCharacterRef->GetIsCrouching()) {
			PlayerCharacterRef->SetIsCrouching(0);
			
		}
		else {
			PlayerCharacterRef->Jump();
		}
	}

	UpdateCameraHeight();

}

void APUBGA_PlayerControllerx::HandleProneTimeFromTable(int32 Pose1, int32 Pose2) {

	//PoseNumber1=Stand,PoseNumber2=Crouch,PoseNumber3=Prone

	FSTR_ProneTimes* ProneTimeRow = nullptr;
	if (Pose1 == 3 && Pose2 == 2) {
		if (PlayerCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_prone_crouch"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_prone_crouch"), TEXT(""));

		}
	}
	if (Pose1 == 3 && Pose2 == 1) {
		if (PlayerCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_prone_stand"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_prone_stand"), TEXT(""));

		}
	}
	if (Pose1 == 2 && Pose2 == 3) {
		if (PlayerCharacterRef->GetIsHoldWeapon()) {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("true_crouch_prone"), TEXT(""));

		}
		else {
			ProneTimeRow = ProneTimeTableObject->FindRow<FSTR_ProneTimes>(FName("false_crouch_prone"), TEXT(""));

		}
	}
	if (Pose1 == 1 && Pose2 == 3) {
		if (PlayerCharacterRef->GetIsHoldWeapon()) {
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
	GetWorldTimerManager().SetTimer(TH_DisableMove, this, &APUBGA_PlayerControllerx::EnableMove, DisableMoveTime, false);




}

void APUBGA_PlayerControllerx::EnableMove() {
	bEnableMove = 1;
}

void APUBGA_PlayerControllerx::UpdateCameraHeight() {

	FSTR_CameraHeight* CameraHeightRow = nullptr;
	if (PlayerCharacterRef->GetIsCrouching()) {
		if (!(PlayerCharacterRef->GetIsHoldWeapon()) && (MoveForwardAxis != 0.f || MoveRightAxis != 0.f)) {

			CameraHeightRow = CameraHeightTableObject->FindRow<FSTR_CameraHeight>(FName("Crouch_Normal_Move"), TEXT(""));
			if (CameraHeightRow) {
				NewHeight = CameraHeightRow->Height;
			}

		}
		else if ((PlayerCharacterRef->GetIsHoldWeapon()) && (MoveForwardAxis != 0.f || MoveRightAxis != 0.f)) {
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
	else if (PlayerCharacterRef->GetIsProne()) {
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
		OriginalHeight = CurrentHeight;
		UpdateCameraHeightWithTL(OriginalHeight, NewHeight);
	}

}

void APUBGA_PlayerControllerx::UpdateCurrentHeight(float UpdatedHeight) {
	//FVector FPS_RelativeLocation = PlayerCharacterRef->GetFPS_Camera()->GetRelativeLocation();
	//FVector FPS_RelativeLoc = FVector(FPS_RelativeLocation.X, FPS_RelativeLocation.Y, UpdatedHeight - 25.f);
	//PlayerCharacterRef->GetFPS_Camera()->SetRelativeLocation(FPS_RelativeLoc);

	FVector CameraBoomRelativeLoc = PlayerCharacterRef->GetCameraBoom()->GetRelativeLocation();
	FVector NewCameraBoomRelativeLoc = FVector(CameraBoomRelativeLoc.X, CameraBoomRelativeLoc.Y, UpdatedHeight);
	PlayerCharacterRef->GetCameraBoom()->SetRelativeLocation(NewCameraBoomRelativeLoc);
	CurrentHeight = UpdatedHeight;
}
