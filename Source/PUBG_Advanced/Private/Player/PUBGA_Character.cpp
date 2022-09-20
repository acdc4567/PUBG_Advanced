// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Player/PUBGA_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values
APUBGA_Character::APUBGA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);

	GetCharacterMovement()->bUseSeparateBrakingFriction = 1;




}

// Called when the game starts or when spawned
void APUBGA_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void APUBGA_Character::MouseTurn(float AxisValue) {

	AddControllerYawInput(AxisValue*.5f);

}

void APUBGA_Character::MouseLookUp(float AxisValue) {

	AddControllerPitchInput(AxisValue*.5f);

}



// Called every frame
void APUBGA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APUBGA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APUBGA_Character::PossessedBy(AController* inController) {

	APUBGA_PlayerController* SPC = Cast<APUBGA_PlayerController>(inController);
	if (SPC) {
		MyPlayerControllerRef = SPC;
		SPC->OnPossessx1(this);

	}
}

void APUBGA_Character::SetIsProne(const bool& Value) {
	bIsProne = Value;
}

void APUBGA_Character::SetIsCrouching(const bool& Value){
	bIsCrouching = Value;
}
void APUBGA_Character::SetIsAiming(const bool& Value){
	bIsAiming = Value;
}