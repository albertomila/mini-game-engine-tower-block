#pragma once
#include <Engine/Systems/IScreen.h>

class CSpriteComponent;
class CGameObject;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;
};

