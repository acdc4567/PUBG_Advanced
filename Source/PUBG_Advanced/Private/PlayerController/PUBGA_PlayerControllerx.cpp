// PUBG Advanced Tutorial. Blueprint To C++!!


#include "PlayerController/PUBGA_PlayerControllerx.h"
#include "Player/PUBGA_Characterx.h"



APUBGA_PlayerControllerx::APUBGA_PlayerControllerx() {


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
