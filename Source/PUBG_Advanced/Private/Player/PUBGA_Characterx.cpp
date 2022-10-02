// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Player/PUBGA_Characterx.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "PlayerController/PUBGA_PlayerControllerx.h"






// Sets default values
APUBGA_Characterx::APUBGA_Characterx()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);




}

// Called when the game starts or when spawned
void APUBGA_Characterx::BeginPlay()
{
	Super::BeginPlay();
	
}

void APUBGA_Characterx::MouseTurn(float AxisValue) {

	AddControllerYawInput(AxisValue);

}

void APUBGA_Characterx::MouseLookUp(float AxisValue) {
	AddControllerPitchInput(AxisValue);


}

// Called every frame
void APUBGA_Characterx::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APUBGA_Characterx::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APUBGA_Characterx::PossessedBy(AController* inController) {

	APUBGA_PlayerControllerx* SPC = Cast<APUBGA_PlayerControllerx>(inController);
	if (SPC) {
		PlayerControllerRef = SPC;
		SPC->OnPossessx(this);
	}


}

