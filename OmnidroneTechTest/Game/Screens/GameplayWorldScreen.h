#pragma once
#include <Engine/Systems/IScreen.h>

class CSpriteComponent;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;
	void Init() override;
	void Update() override;

private:
	CSpriteComponent* _background = nullptr;
	CSpriteComponent* _backgroundPlants = nullptr;
	CSpriteComponent* _foreground = nullptr;
};

