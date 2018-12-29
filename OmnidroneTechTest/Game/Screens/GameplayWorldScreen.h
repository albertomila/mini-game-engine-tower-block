#pragma once
#include <Engine/Systems/IScreen.h>

class CGameObject;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;
	void Init() override;
	void Update() override;

private:
	CGameObject* _background = nullptr;
	CGameObject* _backgroundPlants = nullptr;
	CGameObject* _foreground = nullptr;
};

