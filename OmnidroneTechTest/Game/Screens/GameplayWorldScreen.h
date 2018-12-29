#pragma once
#include <Engine/Systems/IScreen.h>

class CSpriteComponent;
class CGameObject;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;

private:

	CSpriteComponent* _background = nullptr;
	CSpriteComponent* _backgroundPlants = nullptr;
	CSpriteComponent* _foreground = nullptr;
};

