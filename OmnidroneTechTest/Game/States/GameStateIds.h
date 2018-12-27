#pragma once
#include <Engine\StringID.h>

namespace GameStateIds
{
	static const int STATE_ID_MAIN_MENU = CStringID("MainMenuState").GetUniqueID();
	static const int STATE_ID_TUTORIAL = CStringID("TutorialState").GetUniqueID();
	static const int STATE_ID_GAMEPLAY = CStringID("GameplayState").GetUniqueID();
	static const int STATE_ID_FINISH_GAME = CStringID("FinishGame").GetUniqueID();
}