#pragma once
#include <Engine/Systems/IScreen.h>
#include <Game/Screens/StackScoreIndicator.h>

class CButtonObject;
class CTextObject;

class CGameplayHudScreen : public CScreenBase
{
public:
	CGameplayHudScreen();
	~CGameplayHudScreen() override = default;

	void Update() override;
	void PlayScore(int points, const sf::Vector2f& position);

private:
	void InitTextfields();
	void PrintGameStatus();

	CTextObject* _metersTitleText = nullptr;
	CTextObject* _metersText = nullptr;
	CTextObject* _pointsTitleText = nullptr;
	CTextObject* _pointsText = nullptr;
	CTextObject* _livesText = nullptr;
	CStackScoreIndicator _scoreIndicator;
};

