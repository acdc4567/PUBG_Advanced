// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerController.h"
#include "Player/PUBGA_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/PickUpBase.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/PUBGA_GameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "Items/ItemWeapon.h"
#include "Items/PickUpWeapon.h"
#include "Items/PickUpHealth.h"
#include "Items/PickUpEquipment.h"
#include "Items/PickUpFashion.h"
#include "Items/PickUpBoost.h"
#include "Items/PickUpAmmo.h"
#include "Items/PickUpWeaponAcc.h"
#include "Components/BoxComponent.h"
#include "Items/ItemAmmo.h"
#include "Items/ItemWeaponAcc.h"
#include "Items/ItemHealth.h"
#include "Items/ItemBoost.h"
#include "Items/ItemEquipment.h"
#include "Items/ItemFashion.h"



APUBGA_PlayerController::APUBGA_PlayerController() {
	ProneTimeTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ProneTimes.DT_ProneTimes'");
	ProneTimeTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ProneTimeTablePath));

	CameraHeightTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_CameraHeight.DT_CameraHeight'");
	CameraHeightTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *CameraHeightTablePath));

	WalkSpeedTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_WalkSpeed.DT_WalkSpeed'");
	WalkSpeedTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *WalkSpeedTablePath));

	AimAccuratelyTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_AimAccurately.DT_AimAccurately'");
	AimAccuratelyTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AimAccuratelyTablePath));


}

void APUBGA_PlayerController::OnPossessx1(APUBGA_Character* inCharacter) {

	MyCharacterRef = inCharacter;

}

void APUBGA_PlayerController::BeginPlay() {
	Super::BeginPlay();

	PlayerStateRef = Cast<APUBGA_PlayerState>(PlayerState);

	if (PlayerStateRef) {
		PlayerStateRef->OnWeaponChanged.AddDynamic(this, &APUBGA_PlayerController::Event_WeaponChanged);
	
		PlayerStateRef->OnEquipmentChanged.AddDynamic(this, &APUBGA_PlayerController::Event_EquipmentChanged);
	
		PlayerStateRef->OnFashionChanged.AddDynamic(this, &APUBGA_PlayerController::Event_FashionChanged);
		
		PlayerStateRef->OnItemsChanged.AddDynamic(this, &APUBGA_PlayerController::Event_ItemsChanged);

		PlayerStateRef->OnAmmoChanged.AddDynamic(this, &APUBGA_PlayerController::Event_AmmoChanged);

		PlayerStateRef->OnWeaponAccChanged.AddDynamic(this, &APUBGA_PlayerController::Event_WeaponAccChanged);

		MyCharacterRef->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&APUBGA_PlayerController::Event_OnMontageEnded);
	
	
	}

	GameModeRef = Cast<APUBGA_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef) {
		PickupItems = GameModeRef->GeneratedItems;
		SetPickupItems(PickupItems);
	}

	FSTR_AimAccurately* AimAccuratelyRow= AimAccuratelyTableObject->FindRow<FSTR_AimAccurately>(FName("NewRow"), TEXT(""));
	if (AimAccuratelyRow) {
		AimAccuratelyDatas = AimAccuratelyRow;
		AccurateRemaining = AimAccuratelyRow->Duration;
	}


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

	InputComponent->BindAction("Walk", IE_Pressed, this, &APUBGA_PlayerController::WalkKeyPressed);
	InputComponent->BindAction("Walk", IE_Released, this, &APUBGA_PlayerController::WalkKeyReleased);

	InputComponent->BindAction("LeftShift", IE_Pressed, this, &APUBGA_PlayerController::RunKeyPressed);
	InputComponent->BindAction("LeftShift", IE_Released, this, &APUBGA_PlayerController::RunKeyReleased);

	InputComponent->BindAction("Aim", IE_Pressed, this, &APUBGA_PlayerController::AimKeyPressed);
	InputComponent->BindAction("Aim", IE_Released, this, &APUBGA_PlayerController::AimKeyReleased);

	InputComponent->BindAction("DiscardWeapon", IE_Pressed, this, &APUBGA_PlayerController::DiscardKeyPressed);

	InputComponent->BindAction("Interaction", IE_Pressed, this, &APUBGA_PlayerController::InteractionKeyPressed);

	InputComponent->BindAction("TakeBackGun", IE_Pressed, this, &APUBGA_PlayerController::TakeBackKeyPressed);

	InputComponent->BindAction("Keyboard1", IE_Pressed, this, &APUBGA_PlayerController::Keyboard1KeyPressed);

	InputComponent->BindAction("Keyboard2", IE_Pressed, this, &APUBGA_PlayerController::Keyboard2KeyPressed);

	InputComponent->BindAction("ShootMode", IE_Pressed, this, &APUBGA_PlayerController::ShootModeKeyPressed);

	InputComponent->BindAction("Fire", IE_Pressed, this, &APUBGA_PlayerController::FireKeyPressed);
	InputComponent->BindAction("Fire", IE_Released, this, &APUBGA_PlayerController::FireKeyReleased);

	InputComponent->BindAction("Reload", IE_Pressed, this, &APUBGA_PlayerController::ReloadKeyPressed);


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

	TargetingItem();
	UpdateAccurateRemaining(DeltaTime);
	StopAimState();


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
	if (!MyCharacterRef)return;
	if (!(MyCharacterRef->GetIsProne()&&MyCharacterRef->GetIsAiming())) {
		if (MoveForwardAxis != AxisValue) {
			MoveForwardAxis = AxisValue;
			UpdateCameraHeight();
			MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
		}

		if (bEnableMove) {
			UpdateWalkSpeed();
			MovingOnTheGround(1, AxisValue, GetControllerRotation());
		}
	}
	
	
	
}

void APUBGA_PlayerController::MoveRt(float AxisValue) {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsProne() && MyCharacterRef->GetIsAiming())return;


	if (MoveRightAxis != AxisValue) {
		MoveRightAxis = AxisValue;
		UpdateCameraHeight();
		MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
	}

	if (bEnableMove) {
		UpdateWalkSpeed();
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
	
	if (!MyCharacterRef)return;
	ReverseHoldAiming();
	bAltPressed = 1;
	ReleaseFire();
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
		ReleaseFire();
		ReverseHoldAiming();
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

	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());

}


void APUBGA_PlayerController::ProneKeyPressed() {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsProne()) {
		MyCharacterRef->SetIsProne(0);
		ReverseHoldAiming();
		ReleaseFire();
		HandleProneTimeFromTable(3, 1);
	}
	else {
		if (MyCharacterRef->GetIsCrouching()) {
			MyCharacterRef->SetIsAiming(0);
			MyCharacterRef->SetIsCrouching(0);
			MyCharacterRef->SetIsProne(1);
			ReverseHoldAiming();
			ReleaseFire();
			HandleProneTimeFromTable(3, 2);
		}
		else {
			MyCharacterRef->SetIsAiming(0);
			MyCharacterRef->SetIsProne(1);
			ReverseHoldAiming();
			ReleaseFire();
			HandleProneTimeFromTable(1, 3);
		}
	}
	
	UpdateCameraHeight();
	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());

}

void APUBGA_PlayerController::AimKeyPressed() {
	if (!MyCharacterRef)return;
	if (!PlayerStateRef)return;
	if (!(MyCharacterRef->GetIsProne() && (MoveForwardAxis != 0 || MoveRightAxis != 0)) && !MyCharacterRef->GetIsSightAiming()&&(!MyCharacterRef->GetIsPlayingMontage()||MyCharacterRef->GetPlayingMontageType()==EMontageType::EMT_Fire)) {
		RightPressedTime = GetWorld()->GetTimeSeconds();
		if (PlayerStateRef->GetHoldGun()) {
			PlayerStateRef->GetHoldGun()->FireTime = 0.f;
		}


		if (MyCharacterRef->GetIsHoldWeapon()) {
			bHoldAiming = 1;
			MyCharacterRef->SetIsAiming(1);
			MyCharacterRef->HoldAiming(1);
			MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
		}
	}
	

}
void APUBGA_PlayerController::AimKeyReleased() {
	if (!MyCharacterRef)return;

	if (MyCharacterRef->GetIsHoldWeapon()) {
		if (MyCharacterRef->GetIsSightAiming()) {
			MyCharacterRef->SwitchCamera(0);
			MyCharacterRef->HoldAiming(0);
			MyCharacterRef->SetIsSighAiming(0);

		}
		else {
			if (GetWorld()->GetTimeSeconds() - RightPressedTime < .15f) {
				MyCharacterRef->SetIsSighAiming(1);
				bHoldAiming = 0;
			}
			else {
				MyCharacterRef->SetIsAiming(0);
				if (bHoldAiming) {
					bHoldAiming = 0;
					MyCharacterRef->HoldAiming(0);
					MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
				}
			}
		}

	}


	

}

void APUBGA_PlayerController::ReverseHoldAiming() {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsSightAiming()) {
		MyCharacterRef->SwitchCamera(0);
		MyCharacterRef->HoldAiming(0);
		MyCharacterRef->SetIsSighAiming(0);
	}
	else {
		MyCharacterRef->SetIsAiming(0);
		if (bHoldAiming) {
			bHoldAiming = 0;
			MyCharacterRef->HoldAiming(0);
			MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
		}
	}
	
	
	
	
	
}

void APUBGA_PlayerController::JumpKeyPressed() {
	if (!MyCharacterRef)return;


	if (MyCharacterRef->GetIsProne()) {
		MyCharacterRef->SetIsProne(0);
		MyCharacterRef->SetIsCrouching(1);
		ReleaseFire();
		ReverseHoldAiming();
	}
	else {
		if (MyCharacterRef->GetIsCrouching()) {
			MyCharacterRef->SetIsCrouching(0);
		}
		else {
			MyCharacterRef->Jump();
			ReleaseFire();
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
	FVector FPS_RelativeLocation = MyCharacterRef->GetFPS_Camera()->GetRelativeLocation();
	FVector FPS_RelativeLoc = FVector(FPS_RelativeLocation.X, FPS_RelativeLocation.Y,UpdatedHeight-25.f);
	MyCharacterRef->GetFPS_Camera()->SetRelativeLocation(FPS_RelativeLoc);
	CurrentHeight = UpdatedHeight;
}

void APUBGA_PlayerController::WalkKeyPressed() {

	bWalkPressed = 1;

}

void APUBGA_PlayerController::WalkKeyReleased() {
	bWalkPressed = 0;

}

void APUBGA_PlayerController::RunKeyPressed() {
	if (MyCharacterRef) {
		if (MyCharacterRef->GetIsSightAiming()) {
			if (AccurateRemaining>0.f) {
				MyCharacterRef->SetIsAccurateAiming(1);
			}
		}
		else {
			ReverseHoldAiming();
			bRunPressed = 1;
		}
	}
	
}

void APUBGA_PlayerController::RunKeyReleased() {
	if (MyCharacterRef) {
		bRunPressed = 0;
		MyCharacterRef->SetIsAccurateAiming(0);
	}

}

void APUBGA_PlayerController::UpdateWalkSpeed() {
	if (!PlayerStateRef)return;
	int32 HoldWeaponx, Posturex, MoveStatex;

	ReturnThreeIntegers(HoldWeaponx, Posturex, MoveStatex);
	FSTR_WalkSpeed* WalkSpeedRow = nullptr;

	
	/*
	false,true
	stand,crouch,prone
	walk,jog,run,aim
	*/

	if (HoldWeaponx == 0 && Posturex == 1 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_stand_walk"), TEXT(""));
		
	}
	else if(HoldWeaponx == 0 && Posturex == 1 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_stand_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 1 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_stand_run"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 1 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_stand_walk"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 1 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_stand_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 1 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_stand_run"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 1 && MoveStatex == 4) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_stand_aim"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 2 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_crouch_walk"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 2 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_crouch_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 2 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_crouch_run"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 2 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_crouch_walk"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 2 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_crouch_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 2 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_crouch_run"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 2 && MoveStatex == 4) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_crouch_aim"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 3 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_prone_walk"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 3 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_prone_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 0 && Posturex == 3 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("false_prone_run"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 3 && MoveStatex == 1) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_prone_walk"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 3 && MoveStatex == 2) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_prone_jog"), TEXT(""));

	}
	else if (HoldWeaponx == 1 && Posturex == 3 && MoveStatex == 3) {
		WalkSpeedRow = WalkSpeedTableObject->FindRow<FSTR_WalkSpeed>(FName("true_prone_run"), TEXT(""));

	}

	if (WalkSpeedRow) {
		if (MoveForwardAxis>0.f) {
			WalkSpeed = WalkSpeedRow->Forward;
		}
		else {
			WalkSpeed = WalkSpeedRow->Other;
		}
	}

	if (PlayerStateRef->GetHoldGun()) {
		WalkSpeed*= PlayerStateRef->GetHoldGun()->Datas->WalkSpeedPer;
	}



}

void APUBGA_PlayerController::ReturnThreeIntegers(int32& HoldWeapon, int32& Posture, int32& MoveState) {
	if (MyCharacterRef->GetIsHoldWeapon()) {
		HoldWeapon = 1;
	}
	else if(!MyCharacterRef->GetIsHoldWeapon()) {
		HoldWeapon = 0;
	}
	if (MyCharacterRef->GetIsCrouching()) {
		Posture = 2;
	}
	else if(MyCharacterRef->GetIsProne()) {
		Posture = 3;
	}
	else if(!MyCharacterRef->GetIsProne()&&!MyCharacterRef->GetIsCrouching()) {
		Posture = 1;
	}
	if (MyCharacterRef->GetIsAiming()) {
		MoveState = 4;
	}
	else if(!MyCharacterRef->GetIsAiming()&&bWalkPressed) {
		MoveState = 1;
	}
	else if (!MyCharacterRef->GetIsAiming() && bRunPressed) {
		MoveState = 3;
	}
	else if(!MyCharacterRef->GetIsAiming() && !bRunPressed&&!bWalkPressed) {
		MoveState = 2;
	}





}

FName APUBGA_PlayerController::CalculateHoldGunSocket() {
	
	FName GunSocket;
	if (!MyCharacterRef)return FName();
	if (MyCharacterRef->GetIsProne()) {
		if (MoveForwardAxis == 0.f && MoveRightAxis == 0.f) {
			GunSocket = GunProneIdleName;

		}
		else {
			if (MoveRightAxis == 0.f) {
				GunSocket = GunProneFBName;
			}
			else {
				GunSocket = GunProneOtherName;
			}
		}
	}
	else {
		if (MyCharacterRef->GetIsCrouching() && !MyCharacterRef->GetIsAiming()) {
			GunSocket = GunCrouchName;
		}
		else {
			if (MyCharacterRef->GetIsAiming()||MyCharacterRef->GetIsFiring()) {
				GunSocket = GunAimName;
			}
			else {
				if (MyCharacterRef->GetIsReload()) {
					GunSocket = GunReloadName;
				}
				else {
					GunSocket = GunStandName;
				}
			}
		}
	}

	return GunSocket;
}


void APUBGA_PlayerController::Event_WeaponChanged(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand) {
	if (!MyCharacterRef)return;
	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
	UpdateCharacterGunState();


}

void APUBGA_PlayerController::Event_EquipmentChanged(AItemBase* Equipment, bool bIsAdd) {
	if (!MyCharacterRef)return;
	MyCharacterRef->UpdateEquipmentDisplay();
	MyCharacterRef->UpdateWeaponDisplay("None");


}


void APUBGA_PlayerController::Event_FashionChanged(AItemBase* Fashion, bool bIsAdd) {

	if (!MyCharacterRef)return;
	MyCharacterRef->UpdateFashionDisplay();

}

void APUBGA_PlayerController::Event_ItemsChanged(AItemBase* Item, bool bIsAdd) {
	Event_ItemsChanges();

}

void APUBGA_PlayerController::Event_WeaponAccChanged(AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType) {
}

void APUBGA_PlayerController::Event_AmmoChanged(bool bIsTrue) {
	Event_ItemsChanges();
}

void APUBGA_PlayerController::Event_OnMontageEnded(UAnimMontage* Montage, bool bInterrupted) {
	if (!MyCharacterRef)return;
	if (!MyCharacterRef->GetCurrentMontage()) {
		MyCharacterRef->SetIsPlayingMontage(0);
	}


}

void APUBGA_PlayerController::SetPickupItems(TArray<APickUpBase*> Items) {
	if (!Items.IsEmpty()) {
		for (APickUpBase* PickupItem : Items) {
			PickupItem->OnBoxBeginOverlapSign.AddUObject(this, &APUBGA_PlayerController::ExecBeginOverlap);
			PickupItem->OnBoxEndOverlapSign.AddUObject(this, &APUBGA_PlayerController::ExecEndOverlap);
		}


	}



}

void APUBGA_PlayerController::ExecBeginOverlap(APickUpBase* PickupObject) {
	
	ItemsInRange.Add(PickupObject);


}

void APUBGA_PlayerController::ExecEndOverlap(APickUpBase* PickupObject) {
	PickupObject->EnableOutline(0);
	if (!ItemsInRange.IsEmpty()) {
		int32 TempArrayIndex = 0;
		bool bFound = ItemsInRange.Find(PickupObject, TempArrayIndex);
		if (bFound) {
			ItemsInRange.RemoveAt(TempArrayIndex);
		}
	}
	

}

void APUBGA_PlayerController::OutlineItem(APickUpBase* Item) {

	if (!ItemsInRange.IsEmpty()) {
		for (APickUpBase* Itemx : ItemsInRange) {
			if (Itemx == Item) {
				Item->EnableOutline(1);
			}
			else {
				Item->EnableOutline(0);
			}
		}


	}



}

void APUBGA_PlayerController::TargetingItem() {
	if (!MyCharacterRef)return;
	double ShortestDistance = 10000.f;
	APickUpBase* ShortestItem=nullptr;

	if (!ItemsInRange.IsEmpty()) {
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		const FVector TraceStart = MyCharacterRef->GetFollowCamera()->GetComponentLocation();
		const FVector ShootDirection = MyCharacterRef->GetFollowCamera()->GetForwardVector();
		const FVector TraceEnd = TraceStart + ShootDirection * 450.f;
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
		
		for (APickUpBase* ItemInRange : ItemsInRange) {
			ItemInRange->EnableOutline(0);
			double TempDist = FVector::Distance(HitResult.Location, ItemInRange->GetActorLocation());
			if (TempDist <ShortestDistance) {
				ShortestDistance = TempDist;
				ShortestItem = ItemInRange;
			}
		
		
		}

		if (ShortestItem) {
			if (ShortestDistance<65.f) {
				ShortestItem->EnableOutline(1);
				ReadyPickupItem = ShortestItem;
			}
			else {
				ReadyPickupItem = nullptr;
			}
			
		}



	}




}


EWeaponPosition APUBGA_PlayerController::AutoPosition(bool& bIsOnHand) {
	if (!PlayerStateRef)return EWeaponPosition::EWP_MAX;
	int32 CurrentAmount = 0;
	if (PlayerStateRef->GetWeapon1()) {
		CurrentAmount += 1;
	}
	if (PlayerStateRef->GetWeapon2()) {
		CurrentAmount += 1;
	}
	if (PlayerStateRef->GetHoldGun()) {
		CurrentAmount += 1;
	}
	if (CurrentAmount == 0) {
		bIsOnHand = 1;
		return EWeaponPosition::EWP_Left;

	}
	else {
		if (CurrentAmount < 2) {
			if (PlayerStateRef->GetHoldGun()) {
				switch (PlayerStateRef->GetHoldGun()->Position) {
				case EWeaponPosition::EWP_Left:
					bIsOnHand = 0;
					return EWeaponPosition::EWP_Right;
					break;
				case EWeaponPosition::EWP_Right:
					bIsOnHand = 0;
					return EWeaponPosition::EWP_Left;
					break;
				case EWeaponPosition::EWP_MAX:
					break;
				default:
					break;
				}
			}
			else {
				if (PlayerStateRef->GetWeapon1()) {
					bIsOnHand = 0;
					return EWeaponPosition::EWP_Right;

				}
				else {
					bIsOnHand = 0;
					return EWeaponPosition::EWP_Left;

				}
			}
		}
		else {
			if (PlayerStateRef->GetHoldGun()) {
				switch (PlayerStateRef->GetHoldGun()->Position) {
				case EWeaponPosition::EWP_Left:
					bIsOnHand = 1;
					return EWeaponPosition::EWP_Left;

					break;
				case EWeaponPosition::EWP_Right:
					bIsOnHand = 1;
					return EWeaponPosition::EWP_Right;

					break;
				case EWeaponPosition::EWP_MAX:
					break;
				default:
					break;
				}
			}
			else {
				bIsOnHand = 0;
				return EWeaponPosition::EWP_Left;

			}
		}
	}

	return EWeaponPosition::EWP_MAX;

}

void APUBGA_PlayerController::AssignPosition(const EWeaponPosition& Assign, EWeaponPosition& Position, bool& bIsOnHand) {
	if (!PlayerStateRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		if (PlayerStateRef->GetHoldGun()->Position == Assign) {
			Position = Assign;
			bIsOnHand = 1;
		}
		else {
			Position = Assign;
			bIsOnHand = 0;
		}
	}
	else {
		Position = Assign;
		bIsOnHand = 0;
	}



}

APickUpBase* APUBGA_PlayerController::SpawnPickupItems(AItemBase* ItemBase) {
	if (!MyCharacterRef)return nullptr;
	if (!ItemBase)return nullptr;
	APickUpBase* ReturnPUBase=nullptr;
	FName IDx = ItemBase->ID;
	FName SNx = ItemBase->SN;

	FTransform Transformx;
	Transformx.SetLocation(MyCharacterRef->GetActorLocation());
	
	APickUpBase* PUBase=nullptr;
	APickUpWeapon* PUWeapon = nullptr;
	APickUpWeaponAcc* PUWeaponAcc = nullptr;
	APickUpAmmo* PUAmmo = nullptr;
	APickUpHealth* PUHealth = nullptr;
	APickUpBoost* PUBoost = nullptr;
	APickUpEquipment* PUEquipment = nullptr;
	APickUpFashion* PUFashion = nullptr;
	AItemWeapon* ItemWeaponx = nullptr;

	switch (ItemBase->ItemType) {
	case EItemType::EIT_Weapon:
		PUWeapon = GetWorld()->SpawnActorDeferred<APickUpWeapon>(APickUpWeapon::StaticClass(), Transformx);
		if (PUWeapon) {
			PUWeapon->ID = IDx;
			PUWeapon->SN = SNx;
			PUWeapon->Amount = 1;
			ItemWeaponx = Cast<AItemWeapon>(ItemBase);
			if (ItemWeaponx) {
				PUWeapon->Ammo = ItemWeaponx->Ammo;
			}
			PUWeapon->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUWeapon);
		break;
	case EItemType::EIT_Accessories:
		PUWeaponAcc = GetWorld()->SpawnActorDeferred<APickUpWeaponAcc>(APickUpWeaponAcc::StaticClass(), Transformx);
		if (PUWeaponAcc) {
			PUWeaponAcc->ID = IDx;
			PUWeaponAcc->SN = SNx;
			PUWeaponAcc->Amount = 1;
			PUWeaponAcc->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUWeaponAcc);

		break;
	case EItemType::EIT_Ammo:
		PUAmmo = GetWorld()->SpawnActorDeferred<APickUpAmmo>(APickUpAmmo::StaticClass(), Transformx);
		if (PUAmmo) {
			PUAmmo->ID = IDx;
			PUAmmo->SN = SNx;
			PUAmmo->Amount =ItemBase->Amount;
			PUAmmo->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUAmmo);
		break;
	case EItemType::EIT_Health:
		PUHealth = GetWorld()->SpawnActorDeferred<APickUpHealth>(APickUpHealth::StaticClass(), Transformx);
		if (PUHealth) {
			PUHealth->ID = IDx;
			PUHealth->SN = SNx;
			PUHealth->Amount = ItemBase->Amount;
			PUHealth->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUHealth);
		break;
	case EItemType::EIT_Boost:
		PUBoost = GetWorld()->SpawnActorDeferred<APickUpBoost>(APickUpBoost::StaticClass(), Transformx);
		if (PUBoost) {
			PUBoost->ID = IDx;
			PUBoost->SN = SNx;
			PUBoost->Amount = ItemBase->Amount;
			PUBoost->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUBoost);

		break;
	case EItemType::EIT_Helmet:
		PUEquipment = GetWorld()->SpawnActorDeferred<APickUpEquipment>(APickUpEquipment::StaticClass(), Transformx);
		if (PUEquipment) {
			PUEquipment->ID = IDx;
			PUEquipment->SN = SNx;
			PUEquipment->Amount = 1;
			PUEquipment->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUEquipment);
		break;
	case EItemType::EIT_Vest:
		PUEquipment = GetWorld()->SpawnActorDeferred<APickUpEquipment>(APickUpEquipment::StaticClass(), Transformx);
		if (PUEquipment) {
			PUEquipment->ID = IDx;
			PUEquipment->SN = SNx;
			PUEquipment->Amount = 1;
			PUEquipment->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUEquipment);
		break;
	case EItemType::EIT_Backpack:
		PUEquipment = GetWorld()->SpawnActorDeferred<APickUpEquipment>(APickUpEquipment::StaticClass(), Transformx);
		if (PUEquipment) {
			PUEquipment->ID = IDx;
			PUEquipment->SN = SNx;
			PUEquipment->Amount = 1;
			PUEquipment->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUEquipment);
		break;
	case EItemType::EIT_Fashion:
		PUFashion = GetWorld()->SpawnActorDeferred<APickUpFashion>(APickUpFashion::StaticClass(), Transformx);
		if (PUFashion) {
			PUFashion->ID = IDx;
			PUFashion->SN = SNx;
			PUFashion->Amount = 1;
			PUFashion->FinishSpawning(Transformx);

		}
		PUBase = Cast<APickUpBase>(PUFashion);
		break;
	case EItemType::EIT_MAX:


		break;
	default:
		break;
	}
	if (PUBase) {
		PickupItems.Add(PUBase);
		PUBase->OnBoxBeginOverlapSign.AddUObject(this,&APUBGA_PlayerController::ExecBeginOverlap);
		PUBase->OnBoxEndOverlapSign.AddUObject(this, &APUBGA_PlayerController::ExecEndOverlap);
	
		PUBase->GetBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PUBase->GetBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	}
	


	return PUBase;
}


void APUBGA_PlayerController::SpawnPickUpItem( AItemBase* ItemBase, APickUpBase*& PU) {
	PU=SpawnPickupItems(ItemBase);
	
}

void APUBGA_PlayerController::DiscardWeapon(AItemWeapon* ItemWeapon) {
	if (!ItemWeapon)return;
	if (!PlayerStateRef)return;
	if (ItemWeapon->Ammo > 0) {
		AItemAmmo* PUAmmo = nullptr;
		FTransform Transformx;
		Transformx.SetLocation(FVector::ZeroVector);

		PUAmmo = GetWorld()->SpawnActorDeferred<AItemAmmo>(AItemAmmo::StaticClass(), Transformx);
		if (PUAmmo) {
			PUAmmo->ID = ItemWeapon->Datas->UseAmmoID;
			PUAmmo->SN = GenerateSN();
			PUAmmo->Amount = ItemWeapon->Ammo;
			PUAmmo->FinishSpawning(Transformx);

		}
		AItemBase* IBItem = Cast<AItemBase>(PUAmmo);
		if (IBItem) {
			APickUpBase* TempPUBase = nullptr;
			SpawnPickUpItem(IBItem, TempPUBase);
			ItemWeapon->Ammo = 0;
		}
	}
	APickUpBase* TempPUWeapon = nullptr;
	AItemBase* IBWeapon = Cast<AItemBase>(ItemWeapon);
	SpawnPickUpItem(IBWeapon, TempPUWeapon);
	APickUpBase* TempPUWeaponAcc = nullptr;
	if (ItemWeapon->AccSightObj) {
		AItemBase* IBSightAcc = Cast<AItemBase>(ItemWeapon->AccSightObj);
		SpawnPickUpItem(IBSightAcc, TempPUWeaponAcc);
		ItemWeapon->AccSightObj->Destroy();
	}
	if (ItemWeapon->AccForegripObj) {
		AItemBase* IBForegripAcc = Cast<AItemBase>(ItemWeapon->AccForegripObj);

		SpawnPickUpItem(IBForegripAcc, TempPUWeaponAcc);
		ItemWeapon->AccForegripObj->Destroy();
	}
	if (ItemWeapon->AccMagObj) {
		AItemBase* IBMagAcc = Cast<AItemBase>(ItemWeapon->AccMagObj);

		SpawnPickUpItem(IBMagAcc, TempPUWeaponAcc);
		ItemWeapon->AccMagObj->Destroy();
	}
	if (ItemWeapon->AccMuzzleObj) {
		AItemBase* IBMuzzleAcc = Cast<AItemBase>(ItemWeapon->AccMuzzleObj);

		SpawnPickUpItem(IBMuzzleAcc, TempPUWeaponAcc);
		ItemWeapon->AccMuzzleObj->Destroy();
	}
	if (ItemWeapon->AccButtstockObj) {
		AItemBase* IBButtstockAcc = Cast<AItemBase>(ItemWeapon->AccButtstockObj);

		SpawnPickUpItem(IBButtstockAcc, TempPUWeaponAcc);
		ItemWeapon->AccButtstockObj->Destroy();
	}

	if (ItemWeapon->bIsOnHand) {
		PlayerStateRef->SetHoldGun(nullptr);
	}
	else {
		switch (ItemWeapon->Position) {
		case EWeaponPosition::EWP_Left:
			PlayerStateRef->SetWeapon1(nullptr);
			break;
		case EWeaponPosition::EWP_Right:
			PlayerStateRef->SetWeapon2(nullptr);
			break;
		case EWeaponPosition::EWP_MAX:

			break;
		default:
			break;
		}
	}
	ItemWeapon->Destroy();


}


FName APUBGA_PlayerController::GenerateSN() {
	float RandomFloat1 = FMath::RandRange(-1000.f,1000.f);
	float RandomFloat2 = FMath::RandRange(-1000.f, 1000.f);
	FString RandFloat1 = FString::SanitizeFloat(RandomFloat1);
	FString RandFloat2 = FString::SanitizeFloat(RandomFloat2);
	FString RandFloat3 = RandFloat1.Append(RandFloat2);
	return FName(*RandFloat3);

}

void APUBGA_PlayerController::DiscardKeyPressed() {
	if (!MyCharacterRef)return;
	if (!PlayerStateRef)return;
	if (!MyCharacterRef->GetIsProne()&&!MyCharacterRef->GetIsSightAiming()) {
		if (!MyCharacterRef->GetIsPlayingMontage()) {
			if (PlayerStateRef->GetHoldGun()) {
				DiscardWeapon(PlayerStateRef->GetHoldGun());
				ReverseHoldAiming();
			}
			else {
				if (PlayerStateRef->GetWeapon1()) {
					DiscardWeapon(PlayerStateRef->GetWeapon1());
				}
				else {
					if (PlayerStateRef->GetWeapon2()) {
						DiscardWeapon(PlayerStateRef->GetWeapon2());
					}
				}
			}
		}
	}



}


void APUBGA_PlayerController::PickupWeapon(APickUpWeapon* PickupWeaponx, bool bIsAssign, EWeaponPosition Positionx) {
	if (!PlayerStateRef)return;
	EWeaponPosition TargetPosition;
	bool bTargetIsOnHand;
	if (bIsAssign) {
		AssignPosition(Positionx, TargetPosition, bTargetIsOnHand);
	}
	else {
		TargetPosition =AutoPosition(bTargetIsOnHand);
	}
	AItemWeapon* ReplaceWeapon = nullptr;
	if (bTargetIsOnHand) {
		if (PlayerStateRef->GetHoldGun()) {
			ReplaceWeapon = PlayerStateRef->GetHoldGun();
		}
		else {
			if (TargetPosition == EWeaponPosition::EWP_Left) {
				if (PlayerStateRef->GetWeapon1()) {
					ReplaceWeapon = PlayerStateRef->GetWeapon1();
				}
			}
			else if(TargetPosition==EWeaponPosition::EWP_Right) {
				if (PlayerStateRef->GetWeapon2()) {
					ReplaceWeapon = PlayerStateRef->GetWeapon2();
				}
			}
		}
	}
	if (ReplaceWeapon) {
		DiscardWeapon(ReplaceWeapon);
		
	}
	AItemWeapon* IBWeapon = nullptr;
	FTransform Transformx;
	Transformx.SetLocation(FVector::ZeroVector);

	IBWeapon = GetWorld()->SpawnActorDeferred<AItemWeapon>(AItemWeapon::StaticClass(), Transformx);
	if (IBWeapon) {
		IBWeapon->ID = PickupWeaponx->ID;
		IBWeapon->SN = PickupWeaponx->SN;
		IBWeapon->Position = TargetPosition;
		IBWeapon->bIsOnHand = bTargetIsOnHand;
		IBWeapon->Amount = 1;
		IBWeapon->Ammo = PickupWeaponx->Ammo;


		IBWeapon->FinishSpawning(Transformx);
		
		
		if (bTargetIsOnHand) {
			PlayerStateRef->SetHoldGun(IBWeapon);

		}
		else {
			switch (TargetPosition) {
			case EWeaponPosition::EWP_Left:
				PlayerStateRef->SetWeapon1(IBWeapon);
				break;
			case EWeaponPosition::EWP_Right:
				PlayerStateRef->SetWeapon2(IBWeapon);
				break;
			case EWeaponPosition::EWP_MAX:

				break;
			default:
				break;
			}
		}
	}
	

}

bool APUBGA_PlayerController::PickUpItemSuccess() {

	if (ReadyPickupItem) {
		APickUpWeapon* TempPUWeapon = nullptr;
		bool bAssignPos = 0;
		EWeaponPosition WPNPos = EWeaponPosition::EWP_Left;
		bool bPickUpGoodsSuccess = 0;
		bool bPickUpEquipmentSuccess = 0;
		switch (ReadyPickupItem->ItemType) {
		case EItemType::EIT_Weapon:
			TempPUWeapon = Cast<APickUpWeapon>(ReadyPickupItem);
			bAssignPos = 0;
			WPNPos = EWeaponPosition::EWP_Left;
			PickupWeapon(TempPUWeapon, bAssignPos, WPNPos);
			ReadyPickupItem->Destroy();
			return 1;
			break;
		case EItemType::EIT_Accessories:

			bPickUpGoodsSuccess = PickupGoods(ReadyPickupItem);
			if (bPickUpGoodsSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}
			break;
		case EItemType::EIT_Ammo:

			bPickUpGoodsSuccess = PickupGoods(ReadyPickupItem);
			if (bPickUpGoodsSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}

			break;
		case EItemType::EIT_Health:
			bPickUpGoodsSuccess = PickupGoods(ReadyPickupItem);
			if (bPickUpGoodsSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}


			break;
		case EItemType::EIT_Boost:
			bPickUpGoodsSuccess = PickupGoods(ReadyPickupItem);
			if (bPickUpGoodsSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}


			break;
		case EItemType::EIT_Helmet:
			bPickUpEquipmentSuccess = PickupEquipment(ReadyPickupItem);
			if (bPickUpEquipmentSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}

			break;
		case EItemType::EIT_Vest:
			bPickUpEquipmentSuccess = PickupEquipment(ReadyPickupItem);
			if (bPickUpEquipmentSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}

			break;
		case EItemType::EIT_Backpack:
			bPickUpEquipmentSuccess = PickupEquipment(ReadyPickupItem);
			if (bPickUpEquipmentSuccess) {
				ReadyPickupItem->Destroy();
				return 1;
			}
			else {
				return 0;
			}

			break;
		case EItemType::EIT_Fashion:
			PickupFashion(ReadyPickupItem);
			ReadyPickupItem->Destroy();
			break;
		case EItemType::EIT_MAX:


			break;
		default:
			break;
		}


	}
	else {
		return 0;
	}


	return 0;
}


void APUBGA_PlayerController::InteractionKeyPressed() {
	bool bTemp= PickUpItemSuccess();
}

void APUBGA_PlayerController::UpdateCharacterGunState() {
	if (!PlayerStateRef)return;
	if (!MyCharacterRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		MyCharacterRef->SetIsHoldWeapon(1);

	}
	else {
		MyCharacterRef->SetIsHoldWeapon(0);
	}


}


void APUBGA_PlayerController::TakeBackKeyPressed() {
	if (!PlayerStateRef)return;
	if (!MyCharacterRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		ReleaseFire();
		MyCharacterRef->SetIsAiming(0);
		ReverseHoldAiming();
		MyCharacterRef->PlayMontage(EMontageType::EMT_UnEquip);
	}
}

void APUBGA_PlayerController::TakeBackWeapon() {
	if (!MyCharacterRef)return;
	if (!PlayerStateRef)return;
	MyCharacterRef->SetIsHoldWeapon(0);
	PlayerStateRef->GetHoldGun()->bIsOnHand = 0;
	switch (PlayerStateRef->GetHoldGun()->Position) {
	case EWeaponPosition::EWP_Left:
		PlayerStateRef->SetWeapon1(PlayerStateRef->GetHoldGun());
		break;
	case EWeaponPosition::EWP_Right:
		PlayerStateRef->SetWeapon2(PlayerStateRef->GetHoldGun());
		break;
	case EWeaponPosition::EWP_MAX:
		break;
	default:
		break;
	}
	PlayerStateRef->SetHoldGun(nullptr);

	if (ReadyEquipWeapon) {
		MyCharacterRef->PlayMontage(EMontageType::EMT_Equip);
	}

}

void APUBGA_PlayerController::Keyboard1KeyPressed() {
	if (!PlayerStateRef)return;
	if (!MyCharacterRef)return;
	ReadyEquipWeapon = PlayerStateRef->GetWeapon1();
	if (ReadyEquipWeapon) {
		MyCharacterRef->SetIsAiming(0);
		ReverseHoldAiming();
		if (PlayerStateRef->GetHoldGun()) {
			ReleaseFire();
			MyCharacterRef->PlayMontage(EMontageType::EMT_UnEquip);
		}
		else {
			MyCharacterRef->PlayMontage(EMontageType::EMT_Equip);
		}
	}



}


void APUBGA_PlayerController::Keyboard2KeyPressed() {
	if (!PlayerStateRef)return;
	ReadyEquipWeapon = PlayerStateRef->GetWeapon2();
	if (ReadyEquipWeapon) {
		MyCharacterRef->SetIsAiming(0);
		ReverseHoldAiming();
		if (PlayerStateRef->GetHoldGun()) {
			ReleaseFire();
			MyCharacterRef->PlayMontage(EMontageType::EMT_UnEquip);
		}
		else {
			MyCharacterRef->PlayMontage(EMontageType::EMT_Equip);
		}
	}
}

bool APUBGA_PlayerController::PickupGoods(APickUpBase* PUItem) {
	if (!PlayerStateRef)return 0;
	if (!PUItem)return 0;
	if(PlayerStateRef->CheckBackpackCapacity(PUItem->GetWeight())) {
		FTransform Transformx;
		Transformx.SetLocation(FVector::ZeroVector);
		AItemWeaponAcc* IBWeaponAcc = nullptr;
		AItemHealth* IBHealth = nullptr;
		AItemBoost* IBBoost = nullptr;

		AItemBase* CastToIB = nullptr;

		switch (PUItem->ItemType) {
		case EItemType::EIT_Weapon:


			break;
		case EItemType::EIT_Accessories:
			
			IBWeaponAcc= GetWorld()->SpawnActorDeferred<AItemWeaponAcc>(AItemWeaponAcc::StaticClass(), Transformx);
			if (IBWeaponAcc) {
				IBWeaponAcc->ID = PUItem->ID;
				IBWeaponAcc->SN = PUItem->SN;
				IBWeaponAcc->Amount = 1;
				IBWeaponAcc->FinishSpawning(Transformx);
				CastToIB = Cast<AItemBase>(IBWeaponAcc);
				if (CastToIB) {
					PlayerStateRef->AddItem(CastToIB);
				}
			}
			break;
		case EItemType::EIT_Ammo:
			PlayerStateRef->UpdateAmmoAmount(PUItem->ID,1,PUItem->Amount);

			break;
		case EItemType::EIT_Health:
			IBHealth = GetWorld()->SpawnActorDeferred<AItemHealth>(AItemHealth::StaticClass(), Transformx);
			if (IBHealth) {
				IBHealth->ID = PUItem->ID;
				IBHealth->SN = PUItem->SN;
				IBHealth->Amount = PUItem->Amount;
				IBHealth->FinishSpawning(Transformx);
				CastToIB = Cast<AItemBase>(IBHealth);
				if (CastToIB) {
					PlayerStateRef->AddItem(CastToIB);
				}
			}

			break;
		case EItemType::EIT_Boost:
			IBBoost = GetWorld()->SpawnActorDeferred<AItemBoost>(AItemBoost::StaticClass(), Transformx);
			if (IBBoost) {
				IBBoost->ID = PUItem->ID;
				IBBoost->SN = PUItem->SN;
				IBBoost->Amount = PUItem->Amount;
				IBBoost->FinishSpawning(Transformx);
				CastToIB = Cast<AItemBase>(IBBoost);
				if (CastToIB) {
					PlayerStateRef->AddItem(CastToIB);
				}
			}

			break;
		case EItemType::EIT_Helmet:


			break;
		case EItemType::EIT_Vest:


			break;
		case EItemType::EIT_Backpack:


			break;
		case EItemType::EIT_Fashion:


			break;
		case EItemType::EIT_MAX:


			break;
		default:
			break;
		}

		return 1;



	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Backpack Full !!"));
		return 0;
	}




	return 0;
}

void APUBGA_PlayerController::DiscardItem(AItemBase* IBItem) {
	if (!PlayerStateRef)return;
	APickUpBase* PUItem = nullptr;
	PUItem	=SpawnPickupItems(IBItem);
	if (IBItem->ItemType==EItemType::EIT_Ammo) {
		PlayerStateRef->UpdateAmmoAmount(PUItem->ID,0,0);
	}
	bool bRemoved=PlayerStateRef->RemoveItem(IBItem);
	if (IBItem) {
		IBItem->Destroy();
	}




}

bool APUBGA_PlayerController::DiscardEquipment(AItemBase* IBItem, bool bIsCheck) {
	if (!PlayerStateRef)return 0;
	if (bIsCheck) {
		if (IBItem->ItemType == EItemType::EIT_Backpack) {
			if (PlayerStateRef->CheckReplaceBackpack(nullptr)) {

			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Cannot Discard Backpack"));
				return 0;
			}
		}
	}
	
	APickUpBase* PUItemx = SpawnPickupItems(IBItem);
	bool bSuccess= PlayerStateRef->RemoveEquipment(IBItem);
	IBItem->Destroy();

	return 1;
}

bool APUBGA_PlayerController::PickupEquipment(AItemBase* IBItem) {
	if (!PlayerStateRef)return 0;
	if (IBItem->ItemType == EItemType::EIT_Backpack) {
		bool bSuccess = PlayerStateRef->CheckReplaceBackpack(IBItem);
		if (bSuccess) {

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Backpack Capacity is not enough"));
			return 0;
		}
	}
	TArray<AItemBase* > IBEquipments = PlayerStateRef->GetEquipments();
	AItemBase* CurrentItem = nullptr;
	for (AItemBase* IBEquipment:IBEquipments) {
		if (IBEquipment->ItemType==IBItem->ItemType) {
			CurrentItem = IBEquipment;
		}
	}
	if (CurrentItem) {
		bool bSuccessx1= DiscardEquipment(CurrentItem,0);
	}
	AItemEquipment* IBEquipment = nullptr;
	AItemBase* IBEquipmentCastToIB = nullptr;
	FTransform Transformx;
	Transformx.SetLocation(FVector::ZeroVector);
	IBEquipment = GetWorld()->SpawnActorDeferred<AItemEquipment>(AItemEquipment::StaticClass(), Transformx);
	if (IBEquipment) {
		IBEquipment->ID = IBItem->ID;
		IBEquipment->SN = IBItem->SN;
		IBEquipment->Amount = IBItem->Amount;
		IBEquipment->FinishSpawning(Transformx);

		IBEquipmentCastToIB = Cast<AItemBase>(IBEquipment);
		if (IBEquipmentCastToIB) {
			PlayerStateRef->AddEquipment(IBEquipmentCastToIB);
		}
	}




	return 1;
}

void APUBGA_PlayerController::DiscardFashion(AItemBase* IBItem) {
	if (!PlayerStateRef)return;
	APickUpBase* PUItemx = SpawnPickupItems(IBItem);
	bool bRemoved=PlayerStateRef->RemoveFashion(IBItem);
	IBItem->Destroy();

}

void APUBGA_PlayerController::PickupFashion(APickUpBase* PUItem) {
	if (!PlayerStateRef)return;

	APickUpFashion* PUItemx1 = Cast<APickUpFashion>(PUItem);

	TArray<AItemBase*> FashionsDisplayed = PlayerStateRef->GetFashions();

	TArray<AItemBase*> ReplacedItems;

	for (AItemBase* FashionDisplay : FashionsDisplayed) {
		AItemFashion* FashionDisplayx1 = Cast<AItemFashion>(FashionDisplay);
		if (FashionDisplayx1 && PUItemx1) {
			bool bCondition1 = FashionDisplayx1->FashionType == PUItemx1->FashionType;
			bool bCondition2 = FashionDisplayx1->FashionType == EFashionType::EFT_Whole && (PUItemx1->FashionType == EFashionType::EFT_ClothTop || PUItemx1->FashionType == EFashionType::EFT_ClothBottom);
			bool bCondition3 = (FashionDisplayx1->FashionType == EFashionType::EFT_ClothTop || FashionDisplayx1->FashionType == EFashionType::EFT_ClothBottom) && PUItemx1->FashionType == EFashionType::EFT_Whole;
			if (bCondition1|| bCondition2 || bCondition3 ) {
				ReplacedItems.Add(FashionDisplay);
			}



		}

	}

	for (AItemBase* ReplacedItem : ReplacedItems) {
		DiscardFashion(ReplacedItem);

	}
	FTransform Transformx;
	Transformx.SetLocation(FVector::ZeroVector);
	AItemFashion* IBFashion = nullptr;
	AItemBase* IBFashionCastToIB = nullptr;

	IBFashion = GetWorld()->SpawnActorDeferred<AItemFashion>(AItemFashion::StaticClass(), Transformx);
	if (IBFashion) {
		IBFashion->ID = PUItem->ID;
		IBFashion->SN = PUItem->SN;
		IBFashion->Amount = PUItem->Amount;
		IBFashion->FinishSpawning(Transformx);
		IBFashionCastToIB = Cast<AItemBase>(IBFashion);
		if (IBFashionCastToIB) {
			PlayerStateRef->AddFashion(IBFashionCastToIB);
		}
	}



}

bool APUBGA_PlayerController::EquipAccessories(AItemBase* IBItemBase, bool bIsFromGround, AItemWeapon* IWeapon) {
	if (!PlayerStateRef)return 0;

	APickUpWeaponAcc* IBCastToPickupWeaponAcc = nullptr;
	AItemWeaponAcc* IBCastToItemWeaponAcc = nullptr;
	TArray<FName> WeaponIDs;
	
	EWeaponAccType AccType=EWeaponAccType::EWAT_MAX;
	if (bIsFromGround) {
		IBCastToPickupWeaponAcc = Cast<APickUpWeaponAcc>(IBItemBase);
		if (IBCastToPickupWeaponAcc) {
			AccType = IBCastToPickupWeaponAcc->AccType;
			WeaponIDs= IBCastToPickupWeaponAcc->Datas->WeaponIDs;


		}
	}
	else {
		IBCastToItemWeaponAcc=Cast<AItemWeaponAcc>(IBItemBase);
		if (IBCastToItemWeaponAcc) {
			AccType = IBCastToItemWeaponAcc->AccType;
			WeaponIDs = IBCastToItemWeaponAcc->Datas->WeaponIDs;

		}
	}
	int32 TempIndex = 0;
	bool bFound= WeaponIDs.Find(IWeapon->ID,TempIndex);
	
	if (bFound&&(WeaponIDs.Num()>0)) {
		return 0;
	}
	
	AItemWeaponAcc* ReplacedAccObj = nullptr;



	switch (AccType) {
	case EWeaponAccType::EWAT_Sight:
		ReplacedAccObj = IWeapon->AccSightObj;

		break;
	case EWeaponAccType::EWAT_Muzzle:
		ReplacedAccObj = IWeapon->AccMuzzleObj;


		break;
	case EWeaponAccType::EWAT_Foregrip:
		ReplacedAccObj = IWeapon->AccForegripObj;


		break;
	case EWeaponAccType::EWAT_Mag:
		ReplacedAccObj = IWeapon->AccMagObj;


		break;
	case EWeaponAccType::EWAT_Buttstock:
		ReplacedAccObj = IWeapon->AccButtstockObj;


		break;
	case EWeaponAccType::EWAT_MAX:


		break;
	default:
		break;
	}

	if (ReplacedAccObj) {
		int32 TempIBWeaight = IBItemBase->GetWeight();
		int32 TempReplacedAccObjWeight = ReplacedAccObj->GetWeight();
		bool bIsEnough=0;
		if (bIsFromGround) {
			bIsEnough = PlayerStateRef->CheckBackpackCapacity(TempReplacedAccObjWeight);
		}
		else {
			bIsEnough = PlayerStateRef->CheckBackpackCapacity(TempReplacedAccObjWeight - TempIBWeaight);
		}

		if (bIsEnough) {
			AItemBase* ReplacedAccObjCastToIB = Cast<AItemBase>(ReplacedAccObj);
			if (ReplacedAccObjCastToIB) {
				PlayerStateRef->AddItem(ReplacedAccObjCastToIB);
			}
			

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Backpack does not have Capacity for Accessory"));
			return 0;
		}

	}

	AItemBase* WeaponAccObj = nullptr;

	if (bIsFromGround) {
		FTransform Transformx;
		Transformx.SetLocation(FVector::ZeroVector);
		AItemWeaponAcc* IBWeaponAcc = nullptr;
		

		IBWeaponAcc = GetWorld()->SpawnActorDeferred<AItemWeaponAcc>(AItemWeaponAcc::StaticClass(), Transformx);
		if (IBWeaponAcc) {
			IBWeaponAcc->ID= IBItemBase->ID;
			IBWeaponAcc->SN = IBItemBase->SN;
			IBWeaponAcc->Amount = IBItemBase->Amount;
			IBWeaponAcc->FinishSpawning(Transformx);

			WeaponAccObj = Cast<AItemBase>(IBWeaponAcc);
			if (WeaponAccObj) {
				IBItemBase->Destroy();
			}


		}

	}
	else {

		bool bSuccess= PlayerStateRef->RemoveItem(IBItemBase);
		WeaponAccObj = IBItemBase;

	}

	AItemWeaponAcc* WeaponAccObjCastToIWA = Cast<AItemWeaponAcc>(WeaponAccObj);
	if (WeaponAccObjCastToIWA) {
		PlayerStateRef->UpdateWeaponAcc(IWeapon->Position, WeaponAccObjCastToIWA->AccType, WeaponAccObjCastToIWA);
	}


	
	
	return 0;
}

bool APUBGA_PlayerController::RemoveAccessory(AItemBase* ItemAcc, bool bIsToGround, AItemWeapon* Weapon) {
	if (!PlayerStateRef)return 0;
	if (bIsToGround) {
		APickUpBase* PUItem= SpawnPickupItems(ItemAcc);
		AItemWeaponAcc* ItemAccCastToIWA = Cast<AItemWeaponAcc>(ItemAcc);
		if (ItemAccCastToIWA) {
			PlayerStateRef->UpdateWeaponAcc(Weapon->Position, ItemAccCastToIWA->AccType, nullptr);
			ItemAcc->Destroy();
		}
		
	}
	else {
		if (PlayerStateRef->CheckBackpackCapacity(ItemAcc->GetWeight())) {
			AItemWeaponAcc* ItemAccCastToIWA = Cast<AItemWeaponAcc>(ItemAcc);
			if (ItemAccCastToIWA) {
				PlayerStateRef->UpdateWeaponAcc(Weapon->Position, ItemAccCastToIWA->AccType, nullptr);
				PlayerStateRef->AddItem(ItemAcc);
				return 1;
			}

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Backpack Does Not Have Enough Space"));
			return 0;
		}
	}
	
	
	return false;
}







void APUBGA_PlayerController::EquipWeapon() {
	if (!MyCharacterRef)return;
	if (!PlayerStateRef)return;
	if (!ReadyEquipWeapon)return;
	MyCharacterRef->SetIsHoldWeapon(1);

	PlayerStateRef->SetHoldGun(ReadyEquipWeapon);
	ReadyEquipWeapon->bIsOnHand = 1;
	switch (ReadyEquipWeapon->Position) {
	case EWeaponPosition::EWP_Left:
		PlayerStateRef->SetWeapon1(nullptr);
		ReadyEquipWeapon = nullptr;
		break;
	case EWeaponPosition::EWP_Right:
		PlayerStateRef->SetWeapon2(nullptr);
		ReadyEquipWeapon = nullptr;
		break;
	case EWeaponPosition::EWP_MAX:
		break;
	default:
		break;
	}



}



void APUBGA_PlayerController::UpdateAccurateRemaining(float Delta) {
	if (!MyCharacterRef)return;
	if (MyCharacterRef->GetIsAimAccurate()) {
		if (AccurateRemaining > 0.f) {
			AccurateRemaining = FMath::Clamp(AccurateRemaining - Delta, 0.f, 3.f);
		}
		else {
			MyCharacterRef->SetIsAccurateAiming(0);
		}
	}
	else {
		AccurateRemaining = FMath::Clamp(AccurateRemaining + Delta, 0.f, 3.f);
	}


}


void APUBGA_PlayerController::ShootModeKeyPressed() {
	if (!PlayerStateRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		PlayerStateRef->GetHoldGun()->SwitchShootMode();
	}

}

void APUBGA_PlayerController::FireKeyPressed() {
	if (!PlayerStateRef)return;
	if (!MyCharacterRef)return;
	if (PlayerStateRef->GetHoldGun() && !(MyCharacterRef->GetCharacterMovement()->Velocity.Size() != 0.f && MyCharacterRef->GetIsProne()) && bEnableMove && !bAltPressed && !MyCharacterRef->GetCharacterMovement()->IsFalling()) {
		if (!MyCharacterRef->GetIsPlayingMontage()||MyCharacterRef->GetPlayingMontageType()==EMontageType::EMT_Fire) {
			PlayerStateRef->GetHoldGun()->PressFire();
		}
		
	
	}

	


}

void APUBGA_PlayerController::FireKeyReleased() {
	if (!PlayerStateRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		PlayerStateRef->GetHoldGun()->ReleaseFire();
	}
}

void APUBGA_PlayerController::ReleaseFire() {
	if (!PlayerStateRef)return;
	if (PlayerStateRef->GetHoldGun()) {
		PlayerStateRef->GetHoldGun()->ReleaseFire();
	}
}


void APUBGA_PlayerController::StopAimState() {
	if (!MyCharacterRef)return;
	if(!PlayerStateRef)return;
	if (!bHoldAiming && !MyCharacterRef->GetIsSightAiming()) {
		if (PlayerStateRef->GetHoldGun()) {
			if (PlayerStateRef->GetHoldGun()->FireTime > 0.f) {
				if (GetWorld()->GetTimeSeconds() - PlayerStateRef->GetHoldGun()->FireTime > 3.f) {
					MyCharacterRef->SetIsAiming(0);
					PlayerStateRef->GetHoldGun()->FireTime = 0.f;
				}
			}

		}
	}


}


void APUBGA_PlayerController::ReloadKeyPressed() {
	if (!PlayerStateRef)return;
	if (!MyCharacterRef)return;
	if (PlayerStateRef->GetHoldGun() && bEnableMove && !bAltPressed && !MyCharacterRef->GetCharacterMovement()->IsFalling()) {
		if (!MyCharacterRef->GetIsPlayingMontage() || MyCharacterRef->GetPlayingMontageType() == EMontageType::EMT_Fire) {
			PlayerStateRef->GetHoldGun()->ReloadClip();
		}
	}




}


void APUBGA_PlayerController::Event_ReloadEnd() {
	if (!MyCharacterRef)return;
	if (!PlayerStateRef)return;
	if (MyCharacterRef->GetPlayingMontageType()==EMontageType::EMT_Reload) {
		PlayerStateRef->GetHoldGun()->FilledClip();
	}



}









