#pragma once
#include <Engine/Systems/IScreen.h>

class CBaseObject;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;
	void Init() override;
	void Update() override;

private:
	CBaseObject* _background = nullptr;
	CBaseObject* _backgroundPlants = nullptr;
	CBaseObject* _foreground = nullptr;
};

