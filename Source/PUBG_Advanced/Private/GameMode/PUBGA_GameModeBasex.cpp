// PUBG Advanced Tutorial. Blueprint To C++!!


#include "GameMode/PUBGA_GameModeBasex.h"
#include "PlayerController/PUBGA_PlayerControllerx.h"
#include "Player/PUBGA_Characterx.h"
#include "GameState/PUBGA_GameStateBasex.h"
#include "PlayerState/PUBGA_PlayerStatex.h"
#include "UI/PUBGA_HUDx.h"




APUBGA_GameModeBasex::APUBGA_GameModeBasex() {
	DefaultPawnClass = APUBGA_Characterx::StaticClass();
	PlayerControllerClass = APUBGA_PlayerControllerx::StaticClass();
	GameStateClass = APUBGA_GameStateBasex::StaticClass();
	PlayerStateClass = APUBGA_PlayerStatex::StaticClass();
	HUDClass = APUBGA_HUDx::StaticClass();
}
