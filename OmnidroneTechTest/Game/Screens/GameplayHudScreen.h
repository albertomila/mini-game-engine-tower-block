#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonObject;
class CTextObject;

class CGameplayHudScreen : public CScreenBase
{
public:
	CGameplayHudScreen();
	~CGameplayHudScreen() override = default;

	void Update() override;

private:
	void InitTextfields();
	void PrintGameStatus();

	CTextObject* _metersTitleText = nullptr;
	CTextObject* _metersText = nullptr;
	CTextObject* _pointsTitleText = nullptr;
	CTextObject* _pointsText = nullptr;
};

