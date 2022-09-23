// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerController.h"
#include "Player/PUBGA_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PUBGA_Structs.h"
#include "Items/PickUpBase.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/PUBGA_GameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"

APUBGA_PlayerController::APUBGA_PlayerController() {
	ProneTimeTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_ProneTimes.DT_ProneTimes'");
	ProneTimeTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ProneTimeTablePath));

	CameraHeightTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_CameraHeight.DT_CameraHeight'");
	CameraHeightTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *CameraHeightTablePath));

	WalkSpeedTablePath = TEXT("DataTable'/Game/_Blueprints/Datas/DT_WalkSpeed.DT_WalkSpeed'");
	WalkSpeedTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *WalkSpeedTablePath));



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
		
		MyCharacterRef->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&APUBGA_PlayerController::Event_OnMontageEnded);
	
	
	}

	GameModeRef = Cast<APUBGA_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef) {
		PickupItems = GameModeRef->GeneratedItems;
		SetPickupItems(PickupItems);
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
		MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
	}

	if (bEnableMove) {
		UpdateWalkSpeed();
		MovingOnTheGround(1, AxisValue, GetControllerRotation());
	}
	
}

void APUBGA_PlayerController::MoveRt(float AxisValue) {
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

	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());

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
	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());

}

void APUBGA_PlayerController::AimKeyPressed() {
	if (!MyCharacterRef)return;
	MyCharacterRef->SetIsAiming(1);
	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());

}
void APUBGA_PlayerController::AimKeyReleased() {
	if (!MyCharacterRef)return;
	MyCharacterRef->SetIsAiming(0);
	MyCharacterRef->UpdateWeaponDisplay(CalculateHoldGunSocket());
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

void APUBGA_PlayerController::WalkKeyPressed() {

	bWalkPressed = 1;

}

void APUBGA_PlayerController::WalkKeyReleased() {
	bWalkPressed = 0;

}

void APUBGA_PlayerController::RunKeyPressed() {

	bRunPressed = 1;
}

void APUBGA_PlayerController::RunKeyReleased() {

	bRunPressed = 0;
}

void APUBGA_PlayerController::UpdateWalkSpeed() {

	int32 HoldWeaponx, Posturex, MoveStatex;

	ReturnThreeIntegers(HoldWeaponx, Posturex, MoveStatex);
	FSTR_WalkSpeed* WalkSpeedRow = nullptr;

	//UE_LOG(LogTemp, Warning, TEXT("% d, % d, % d"), HoldWeaponx, Posturex, MoveStatex);
	
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







