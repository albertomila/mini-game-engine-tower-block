#pragma once
#include <Engine/Systems/IScreen.h>
#include <Game/Screens/StackScoreIndicator.h>

class CButtonComponent;
class CTextComponent;

class CGameplayHudScreen : public CScreenBase
{
public:
	CGameplayHudScreen();
	~CGameplayHudScreen() override = default;

	void Update() override;
	void PlayScore(float accuracyNormalized, int points, const sf::Vector2f& worldPosition);

private:
	void InitTextfields();
	void PrintGameStatus();

	CTextComponent* _metersTitleText = nullptr;
	CTextComponent* _metersText = nullptr;
	CTextComponent* _pointsTitleText = nullptr;
	CTextComponent* _pointsText = nullptr;
	CTextComponent* _livesText = nullptr;
	CStackScoreIndicator _scoreIndicator;
};

