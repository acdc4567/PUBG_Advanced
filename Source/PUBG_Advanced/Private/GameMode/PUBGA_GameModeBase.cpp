// PUBG Advanced Tutorial. Blueprint To C++!!


#include "GameMode/PUBGA_GameModeBase.h"
#include "Player/PUBGA_Character.h"
#include "GameState/PUBGA_GameStateBase.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "UI/PUBGA_HUD.h"


APUBGA_GameModeBase::APUBGA_GameModeBase() {
	DefaultPawnClass = APUBGA_Character::StaticClass();
	GameStateClass = APUBGA_GameStateBase::StaticClass();
	PlayerControllerClass = APUBGA_PlayerController::StaticClass();
	PlayerStateClass = APUBGA_PlayerState::StaticClass();
	HUDClass = APUBGA_HUD::StaticClass();



}
